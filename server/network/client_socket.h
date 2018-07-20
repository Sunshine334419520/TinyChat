//
// Created by Sunshine on 2018/7/19.
//

#ifndef TINYCHATSERVER_CLIENT_SOCKET_H
#define TINYCHATSERVER_CLIENT_SOCKET_H

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

class ClientSocket final {
 public:
    ClientSocket() noexcept;

    static ClientSocket* Create();


    void Connect();

    void Destroy() noexcept;

 private:
    void Init();
    Socket client_fd_;
    bool is_connect_;

};


}   // namespace network


#endif //TINYCHATSERVER_CLIENT_SOCKET_H
