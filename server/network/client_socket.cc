//
// Created by Sunshine on 2018/7/19.
//

#include "client_socket.h"


#include <cassert>


#include "exception/tiny_chat_exception.h"


namespace network {

namespace {

const int kServPort = 9996;
const char kServAddr[] = "127.0.0.1";

ClientSocket* g_ClientInstance = nullptr;
}

ClientSocket::ClientSocket() noexcept
    : is_connect_(false){
}

ClientSocket *ClientSocket::Create() {
   if (!g_ClientInstance)
       g_ClientInstance = new ClientSocket();

   return g_ClientInstance;
}

void ClientSocket::Connect() {
    Init();

    try {
        client_fd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (client_fd_ < 0)
            throw mistake::socket_exception("socket connect error!");

        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));

        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(kServPort);

        #if defined(OS_POSIX)
            if (inet_pton(AF_INET, kServAddr, &servaddr.sin_addr) < 0)
                throw mistake::socket_exception("inet_pton connect error");
        #else
            servaddr.sin_addr.S_un.S_addr = inet_addr(kServAddr);
        #endif

           if (connect(client_fd_, (sockaddr*)&servaddr, sizeof(servaddr)) < 0)
               throw mistake::socket_exception("connect error !");

    } catch(...) {
        Destroy();
        throw ;
    }
}

void ClientSocket::Destroy() noexcept {
    assert(g_ClientInstance);
    if (is_connect_) {
#if defined(OS_WIN)
        WSACleanup();
#endif
    }

    delete g_ClientInstance;
    g_ClientInstance = nullptr;
}

void ClientSocket::Init() {
#if defined(OS_WIN)
    WORD sock_version = MAKEWORD(2, 2);
    WSADATA wsaData;
    try {
        if (WSAStartup(sock_version, &wsaData) != 0) {
            throw mistake::socket_exception("WSAstartup init error!");
        }
    } catch(...) {
        Destroy();
        throw ;
    }
#endif
}


ssize_t ClientSocket::Recv(Socket connfd, char *buffer, size_t len) {

    ssize_t ret = recv(connfd, buffer, len, 0);

    if (ret < 0)
        throw mistake::socket_exception(-1, "recv error");

    return ret;
}

ssize_t ClientSocket::Send(Socket connfd, const char *buffer, size_t len) {
    ssize_t ret  = send(connfd, buffer, len, 0);

    if (ret < 0)
        throw mistake::socket_exception(-2, "recv error");

    return ret;
}


}   // namespace network.