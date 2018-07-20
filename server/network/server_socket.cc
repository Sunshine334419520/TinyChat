#include "network/server_socket.h"

#include <cassert>


#include "exception/tiny_chat_exception.h"

namespace network {

namespace {

const int kDefaultServPort = 9996; 
const char kDefaultServAddr[] = "127.0.0.1";
const int kListenQ = 20;

ServerSocket* g_ServInstance = nullptr;

}   // namespace.


ServerSocket::ServerSocket() noexcept
    : is_listen_(false){}

// static 
ServerSocket* ServerSocket::Create() {
    if (g_ServInstance)
        g_ServInstance = new ServerSocket();
    return g_ServInstance;
}


void ServerSocket::Destroy() noexcept {
    // g_Instance 必须不为空
    assert(g_ServInstance);

    // if true, The is_listen_, then Call shutdown
    if (is_listen_) {
        shutdown(listen_fd_, 1);
        is_listen_ = false;
    }

    delete g_ServInstance;
}

void ServerSocket::Listen() {
    listen_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_fd_ < 0)
        throw mistake::socket_exception("socket error");
    
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(kDefaultServPort);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    const int on = 1;

    try {
        if (setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
            throw mistake::socket_exception("setsockopt error");
    } catch(...) {
        close(listen_fd_);
        throw ;
    }

    try {
        if (bind(listen_fd_, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
            throw mistake::socket_exception("bind error");
    } catch(...) {
        close(listen_fd_);
        throw ;
    }

    try {
        if (listen(listen_fd_, kListenQ) < 0)
            throw mistake::socket_exception("listen_fd_");
    } catch(...) {
        close(listen_fd_);
        throw ;
    }
    
}

Socket ServerSocket::Accept() {
    assert(is_listen_);

    Socket client_fd;

    struct sockaddr_in client_addr;
    socklen_t client_len;
    try {
        if ( ( client_fd = accept(listen_fd_, (sockaddr*)&client_addr, &client_len)) < 0)
            throw mistake::socket_exception("accept error");
    } catch(...) {
        close(listen_fd_);
        throw ;
    }

    return client_fd;
}



}   // namespace network