/**
 * Socket Stuff
 */
#pragma once

#include "cpch.hpp"
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
        virtual auto Send(ScopePtr<PacketOut>) -> void = 0;

        /**
         * Receives a PacketIn
        **/
        virtual auto Recv() -> RefPtr<PacketIn> = 0;

        /**
         * Sets the socket to be blocking / non-blocking
         *
         * @param blocking - Whether or not to block.
        **/
        virtual auto SetBlock(bool blocking) -> bool = 0;

        /**
         * Closes the socket.
        **/
        virtual auto Close() -> void = 0;

        /**
         * Returns whether or not the connection is alive?
        **/
        virtual auto isAlive() -> bool = 0;

    protected:
        int m_socket = 0;
    };

    /**
     * Socket for Client side connections
    **/
    class ClientSocket : public Socket {
    public:
        ClientSocket();
        virtual ~ClientSocket();

        /**
         * Connects to an IP at a port number.
        **/
        auto Connect(unsigned short port, const char* ip) -> bool;

        auto Close() -> void;
        auto SetBlock(bool blocking) -> bool;
        auto Send(ScopePtr<PacketOut> packetOut) -> void;
        auto isAlive() -> bool;

        auto Recv() -> RefPtr<PacketIn>;

        /**
         * Threshold for zlib compression.
        **/
        size_t threshold;
    };

    /**
     * Creates a Connection.
     * Used with a raw connection socket.
     * Provides us packet methods.
     */
    class Connection {
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
        auto SetBlock(bool blocking) -> bool;

        /**
         * Checks if connection is valid.
         *
         * \return - Connection validity.
         */
        auto isAlive() -> bool;

        /**
         * Send a packet out  - (will be consumed)
         * @param packetOut - Packet to send
         */
        auto Send(ScopePtr<PacketOut> packetOut) -> void;

        /**
         * Packet Receive.
         * \return - Packet
         */
        auto Recv() -> RefPtr<PacketIn>;

        /**
         * Closes our connection.
         * Is also done at end of scope if not already done.
         */
        auto Close() -> void;

    private:
        s32 m_socket;
        bool connected;
    };

    /**
     * Creates a server socket for binding.
     */
    class ServerSocket {
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