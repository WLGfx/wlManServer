#include "tcpserver.hpp"

#include <thread>

TCPServer::TCPServer(bool start_, int port, int backlog, int timeout, int maxConnections)
{
    port_ = port;
    backlog_ = backlog;
    timeout_ = timeout;
    maxConnections_ = maxConnections;
    
    status_.running = false;
    quit_ = false;
    
    if (start_) {
        start();
    }
}

TCPServer::~TCPServer()
{
    quit(true);
}

TCPServer::ServerStatus TCPServer::start()
{
    // set thread_ up with callable
    thread_ = std::thread([&] { run(); });
    return status_;
}

void TCPServer::run()
{
    status_.running = true;

    // TODO: Here be dragons
    std::this_thread::sleep_for(std::chrono::seconds(1));

    status_.running = false;
}

void TCPServer::quit(bool join)
{
    quit_ = true;
    if (join) {
        thread_.join();
    }
}

