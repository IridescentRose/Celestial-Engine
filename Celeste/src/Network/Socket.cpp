/**
 * Socket implementation
 */
#include <Network/Socket.hpp>

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <ws2tcpip.h>

namespace Celeste::Network{

    ClientSocket::ClientSocket() {
        m_socket = 0;
    }

    [[maybe_unused]] auto ClientSocket::Connect(unsigned short port, const char* ip) -> bool {
        CS_CORE_INFO("Opening Connection: [" + std::string(ip) + "]" + "@" + std::to_string(port));

        m_socket = static_cast<int>(socket(PF_INET, SOCK_STREAM, 0));
        struct sockaddr_in name{};
        name.sin_family = AF_INET;
        name.sin_port = htons(port);

        inet_pton(AF_INET, ip, &name.sin_addr.s_addr);
        bool b = (connect(m_socket, (struct sockaddr*) & name, sizeof(name)) >= 0);

        if(!b) {
            CS_CORE_ERROR("Failed to open a connection! (Is the server open?)");
        }

        return b;
    }

    auto Socket::Close() const -> void {
        CS_CORE_INFO("Closing Client Socket!");
        using namespace Platform;

        if constexpr (isPlatform(PlatformType::Windows)) {
            closesocket(m_socket);
        }
    }

    auto nix_SetBlock([[maybe_unused]] int m_socket, [[maybe_unused]]  bool blocking) {
        #if BUILD_PLAT != BUILD_WINDOWS
        if (blocking) {
            int flags = fcntl(m_socket, F_GETFL, 0);
            flags &= ~O_NONBLOCK;
            fcntl(m_socket, F_SETFL, flags);
        }
        else {
            fcntl(m_socket, F_SETFL, O_NONBLOCK);
        }
        return true;
        #else
        return false;
        #endif
    }

    auto ms_SetBlock(int m_socket, bool blocking) {
        #if BUILD_PLAT == BUILD_WINDOWS
        unsigned long iMode = !blocking;
        int iResult = ioctlsocket(m_socket, FIONBIO, &iMode);
        if (iResult != NO_ERROR) {
            return false;
        }
        return true;
        #else
        return false
        #endif
    }

    [[maybe_unused]] auto Socket::Send(ScopePtr<PacketOut> packetOut) const -> void {
        size_t packetLength = packetOut->buffer->GetUsedSpace() + 1;

        auto byteBuffer = createScopePtr<ByteBuffer>(packetLength + 5); //512 KB
        byteBuffer->WriteVarInt32(static_cast<uint32_t>(packetLength));
        byteBuffer->WriteBEUInt8(packetOut->ID);

        for (int i = 0; i < packetOut->buffer->GetUsedSpace(); i++) {
            uint8_t temp;
            packetOut->buffer->ReadBEUInt8(temp);
            byteBuffer->WriteBEUInt8(temp);
        }

        int res = send(m_socket, byteBuffer->m_Buffer, static_cast<int>(byteBuffer->GetUsedSpace()), 0);
        if (res < 0) {
            CS_CORE_WARN("Failed to send a packet!");
            CS_CORE_WARN("Packet Size: " + std::to_string(packetOut->buffer->GetUsedSpace()));
        }
    }

    [[maybe_unused]] auto Socket::isAlive() const -> bool {
        bool connected = false;
        char buffer[32] = { 0 };
        int res = recv(m_socket, buffer, sizeof(buffer), MSG_PEEK);

        if (res != 0) {
            connected = true;
        }

        return connected;
    }

    [[maybe_unused]] auto Socket::Recv() const -> RefPtr<PacketIn> {
        std::vector<byte> len;
        byte newByte;
        int res = recv(m_socket, &newByte, 1, MSG_PEEK);

        if (res > 0) {
            char data[5] = { 0 };
            size_t dataLen = 0;
            do {
                size_t totalReceived = 0;
                while (1 > totalReceived) {
                    size_t received = recv(m_socket, &data[dataLen] + totalReceived, static_cast < int>(1 - totalReceived), 0);
                    if (received <= 0) {
                        Platform::delayForMS(1);
                    }
                    else {
                        totalReceived += received;
                    }
                }
            } while ((data[dataLen++] & 0x80) != 0);

            int readed = 0;
            int result = 0;
            char read;
            do {
                read = data[readed];
                int value = (read & 0b01111111);
                result |= (value << (7 * readed));
                readed++;
            } while ((read & 0b10000000) != 0);


            int length = result;

            auto pIn = new PacketIn(length);
            CS_CORE_DEBUG("LENGTH: " + std::to_string(length));

            int totalTaken = 0;

            byte* b = new byte[length];
            for (int i = 0; i < length; i++) {
                b[i] = 0;
            }

            while (totalTaken < length) {
                res = recv(m_socket, b, length, 0);
                if (res > 0) {
                    totalTaken += res;
                }
                else {
                    Platform::delayForMS(1);
                }
            }


            for (int i = 0; i < length; i++) {
                pIn->buffer->WriteBEUInt8(b[i]);
            }

            if (pIn->buffer->GetUsedSpace() > 0) {
                uint8_t t = 0;
                pIn->buffer->ReadBEUInt8(t);
                pIn->ID = t;
            }
            else {
                pIn->ID = -1;
            }



            CS_CORE_DEBUG("Received Packet!");
            CS_CORE_DEBUG("Packet ID: " + std::to_string(pIn->ID));

            return RefPtr<PacketIn>{pIn};
        }
        else {
            return nullptr;
        }
    }

    Connection::Connection(s32 sock) {
        m_socket = sock;
        SetBlock(false);
    }

    auto Socket::SetBlock(bool blocking) const -> bool {
        using namespace Platform;

        if constexpr (isPlatform(PlatformType::Windows)) {
            return ms_SetBlock(m_socket, blocking);
        } else {
            return nix_SetBlock(m_socket, blocking);
        }
    }

    Socket::~Socket() {
        Close();
    }

    [[maybe_unused]] ServerSocket::ServerSocket(u16 port) {
        m_socket = static_cast<int>(socket(AF_INET, SOCK_STREAM, 0));

        if (m_socket == -1) {
            throw std::runtime_error("Fatal: Could not open socket! Errno: " + std::to_string(errno));
        }
        m_PortNo = port;



        CS_CORE_DEBUG("Socket Created!");

        sockaddr_in sockaddr{};
        sockaddr.sin_family = AF_INET;
        sockaddr.sin_addr.s_addr = INADDR_ANY;
        sockaddr.sin_port = htons(port);

        if (bind(m_socket, (struct sockaddr*) & sockaddr, sizeof(sockaddr)) < 0) {
            throw std::runtime_error("Fatal: Could not bind socket address! Port: " + std::to_string(port) + ". Errno: " + std::to_string(errno));
        }

        CS_CORE_DEBUG("Socket Bound!");

    }

    ServerSocket::~ServerSocket() {
        Close();
    }

    void ServerSocket::Close() const {
        CS_CORE_INFO("Closing Server Socket!");
        using namespace Platform;

        if constexpr (isPlatform(PlatformType::Windows)) {
            closesocket(m_socket);
        }
    }

    [[maybe_unused]] auto ServerSocket::ListenState() const -> RefPtr <Connection> {
        sockaddr_in socketAddress{};
        socketAddress.sin_family = AF_INET;
        socketAddress.sin_addr.s_addr = INADDR_ANY;
        socketAddress.sin_port = htons(m_PortNo);

        CS_CORE_DEBUG("Listening on socket...");
        if (listen(m_socket, 1) < 0) {
            throw std::runtime_error("Fatal: Could not listen on socket. Errno: " + std::to_string(errno));
        }

        auto addressLen = sizeof(socketAddress);
        auto conn = static_cast<int>(accept(m_socket, (struct sockaddr*) & socketAddress, (socklen_t*)&addressLen));
        CS_CORE_DEBUG("Found potential connection...");

        if (conn < 0) {
            throw std::runtime_error("Fatal: Could not accept connection. Errno: " + std::to_string(errno));
        }

        CS_CORE_INFO("New Connection from " + std::string((inet_ntoa(socketAddress.sin_addr))) + " on port " + std::to_string(ntohs(socketAddress.sin_port)));

        return createRefPtr<Connection>(conn);
    }
}