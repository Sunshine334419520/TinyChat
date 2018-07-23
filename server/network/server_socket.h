
#ifndef TINYCHATSERVER_SERVER_SOCKET_H
#define TINYCHATSERVER_SERVER_SOCKET_H

#include "macor.h"



#if defined(OS_WIN)

 #include <winsock2.h>
 #pragma comment(lib,"ws2_32.lib")#if defined(OS_WIN)
 #include "windows.h"

 namespace network {

 using Socket = SOCKET;

 }

#endif

#if defined(OS_POSIX)

 #include <netinet/in.h>
 #include <sys/socket.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <unistd.h>
 #include <arpa/inet.h>

namespace network {

 using Socket = int;

}   // namespace network

#endif 


namespace network {

/*
enum class IP {
    IPV4 = 0x01,
    IPV6
};

enum class PROTOCOL {
    TCP = 0x64,
    UDP = 0x72,
    SCTP = 0x80
};

struct SockInfo {
    IP ip;
    PROTOCOL protocol;
    int port;
    char* address;
};
*/


class ServerSocket final {
 public:
    ServerSocket()noexcept;

    static ServerSocket* Create();
    void Listen();
    Socket Accept();

    // 这只是一个不同的发送与接收函数. 发送大数据时需要进行额外的处理
    ssize_t Recv(Socket connfd, char* buffer, size_t len);
    ssize_t Send(Socket connfd, const char* buffer, size_t len);

    // 必须用这个函数
    void Destroy() noexcept;
    
 private:
    Socket listen_fd_;      // listen socket
    bool is_listen_;
 private:
    ONLYALLOW_HEAP_ALLOC_AND_NOTEXTEND(ServerSocket);
};


}   // namespace network

#endif