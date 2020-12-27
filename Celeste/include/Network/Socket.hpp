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
        virtual ~Socket();

        /**
         * Send a packet - (will be consumed)
        **/
        [[maybe_unused]] [[maybe_unused]] auto Send(ScopePtr<PacketOut>) const -> void ;

        /**
         * Receives a PacketIn
        **/
        [[maybe_unused]] [[maybe_unused]] auto Recv() const -> RefPtr<PacketIn>;

        /**
         * Sets the socket to be blocking / non-blocking
         *
         * @param blocking - Whether or not to block.
        **/
        [[maybe_unused]] auto SetBlock(bool blocking) const -> bool;

        /**
         * Closes the socket.
        **/
        [[maybe_unused]] auto Close() const -> void;

        /**
         * Returns whether or not the connection is alive?
        **/
        [[maybe_unused]] [[maybe_unused]] auto isAlive() const -> bool;

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
        [[maybe_unused]] [[maybe_unused]] auto Connect(unsigned short port, const char* ip) -> bool;
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
        [[maybe_unused]] ServerSocket(u16 port);
        ~ServerSocket();

        /**
         * Listen for a connection
        **/
        [[maybe_unused]] auto ListenState() const -> RefPtr<Connection>;

        /**
         * Closes our socket.
         */
        void Close() const;

    private:
        s32 m_socket;
        u16 m_PortNo;
    };

    //TODO: Implement Sockets
}