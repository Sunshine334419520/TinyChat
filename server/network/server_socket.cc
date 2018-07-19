#include "network/server_socket.h"

#include <cassert>

namespace network {

namespace {

const int kDefaultServPort = 9996; 
const char kDefaultServAddr[] = "127.0.0.1";
const int kListenQ = 20;

ServerSocket* g_Instance = nullptr;

}

// static 
ServerSocket* ServerSocket::Create() {
    if (g_Instance)
        g_Instance = new ServerSocket();
    return g_Instance;
}


// static
void ServerSocket::Destroy() noexcept {
    assert(g_Instance);
    assert(listen_fd_);

    shotdown(listen_fd_);
    delete g_Instance;
}

void ServerSocket::Listen() {
    listen_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listen_fd_ < 0)
        throw socket_exception("socket error");
    
    struct sockaddr_in serv_addr;
    bzero(&serv_addr, sizeof(servaddr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(kDefaultServPort);
    serv_addr.sin_addr.S_addr = htonl(kDefaultServAddr);

    const int on = 1;

    try {
        if (setsockopt(listen_fd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
            throw socket_exception("setsockopt error");
    } catch(...) {
        close(listen_fd_);
        throw ;
    }

    try {
        if (bind(listen_fd_, (sockeaddr*)&serv_addr), sizeof(servaddr)) < 0)
            throw socket_exception("bind error");
    } catch(...) {
        close(listen_fd_);
        throw ;
    }

    try {
        if (listen(listen_fd_, kListenQ) < 0)
            throw sockete_exception("listen_fd_");
    } catch(...) {
        close(listen_fd_);
        throw ;
    }
    
}

Socket ServerSocket::Accept() {
    assert(is_listen_);

    struct sockaddr_in client_addr;
    socket_t client_len;
    try {
        if (client_addr = accept(listen_fd_, (sockaddr*)&client_addr, &client_len) < 0)
            throw socket_exception("accept error");
    } catch(...) {
        close(listen_fd_);
        throw ;
    }
}



}