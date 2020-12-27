/**
 * Socket Stuff
 */
#pragma once

//#include "cpch.hpp"
#include "Packet.hpp"

namespace Celeste::Network {
    /**
	 * Abstract Socket interface
	**/
    class Socket {
    public:
        virtual ~Socket() = default;

        /**
         * Send a packet - (will be consumed)
        **/
        [[maybe_unused]] virtual auto Send(ScopePtr<PacketOut>) -> void = 0;

        /**
         * Receives a PacketIn
        **/
        [[maybe_unused]] virtual auto Recv() -> RefPtr<PacketIn> = 0;

        /**
         * Sets the socket to be blocking / non-blocking
         *
         * @param blocking - Whether or not to block.
        **/
        [[maybe_unused]] virtual auto SetBlock(bool blocking) -> bool = 0;

        /**
         * Closes the socket.
        **/
        [[maybe_unused]] virtual auto Close() -> void = 0;

        /**
         * Returns whether or not the connection is alive?
        **/
        [[maybe_unused]] virtual auto isAlive() -> bool = 0;

    protected:
        int m_socket = 0;
    };

    /**
     * Socket for Client side connections
    **/
    class [[maybe_unused]] ClientSocket : public Socket {
    public:
        ClientSocket();
        ~ClientSocket() override = default;

        /**
         * Connects to an IP at a port number.
        **/
        [[maybe_unused]] auto Connect(unsigned short port, const char* ip) -> bool;

        auto Close() -> void override;
        auto SetBlock(bool blocking) -> bool override;
        auto Send(ScopePtr<PacketOut> packetOut) -> void override;
        auto isAlive() -> bool override;

        auto Recv() -> RefPtr<PacketIn> override;
    };

    /**
     * Creates a Connection.
     * Used with a raw connection socket.
     * Provides us packet methods.
     */
    class Connection : public Socket {
    public:
        /**
         * Constructs a new Connection.
         *
         * \param sock - accepted TCP connection
         */
        Connection(s32 sock);

        /**
         * Destruction.
         *
         */
        ~Connection();

        /**
         * Turns on or off non-blocking mode.
         *
         * \param blocking - True if blocking, false if non-blocking. By default is blocking.
         * \return - Whether or not operation was successful
         */
        auto SetBlock(bool blocking) -> bool override;

        /**
         * Checks if connection is valid.
         *
         * \return - Connection validity.
         */
        auto isAlive() -> bool override;

        /**
         * Send a packet out  - (will be consumed)
         * @param packetOut - Packet to send
         */
        auto Send(ScopePtr<PacketOut> packetOut) -> void override;

        /**
         * Packet Receive.
         * \return - Packet
         */
        auto Recv() -> RefPtr<PacketIn> override;

        /**
         * Closes our connection.
         * Is also done at end of scope if not already done.
         */
        auto Close() -> void override;

    private:
        s32 m_socket;
        bool connected;
    };

    /**
     * Creates a server socket for binding.
     */
    class [[maybe_unused]] ServerSocket {
    public:

        /**
         * Creates socket and binds it and listens to it.
         *
         * @param port - Port to listen to.
        **/
        ServerSocket(u16 port);
        ~ServerSocket();

        /**
         * Listen for a connection
        **/
        auto ListenState() -> RefPtr<Connection>;

        /**
         * Closes our socket.
         */
        void Close();

    private:
        s32 m_socket;
        u16 m_PortNo;
    };

    //TODO: Implement Sockets
}