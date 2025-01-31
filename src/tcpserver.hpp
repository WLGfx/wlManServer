// add header guard
#ifndef TCPSERVER_HPP
#define TCPSERVER_HPP

#include <atomic>
#include <thread>

extern "C" {
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/ioctl.h>
}

class TCPServer {
public:
    TCPServer(bool start, int port = 8080, int backlog = 10, int timeout = 10, int maxConnections = 10);
    ~TCPServer();

    // For fetching server status
    class ServerStatus { // TODO: more service data here
    public:
        ServerStatus() {}
        ~ServerStatus() {}
        bool running = false;
    };

    // ####
    // Servers socket connector
    class ServerSocket {
    public:
        int sockfd_;
        bool error_;

        ServerSocket() {}
        ~ServerSocket() {}

        void connect(const char* address, int port);
    };
    // ####

    void run(int port, int backlog, int timeout, int maxConnections);

    ServerStatus start();
    void run();
    void quit(bool join = true);

    ServerStatus status() { return status_; }

private:
    int port_;
    int backlog_;
    int timeout_;
    int maxConnections_;
    std::atomic<bool> quit_;

    std::thread thread_;
    ServerSocket socket_;
    ServerStatus status_;
};

#endif