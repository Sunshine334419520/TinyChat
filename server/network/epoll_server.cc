//
// Created by Sunshine on 2018/7/20.
//

#include "epoll_server.h"


namespace network {

EpollServer::EpollServer(bool et)
    : epoll_fd_(-1),
      pervs_(nullptr),
      et_(et),
      max_connections_(1024){}

EpollServer::~EpollServer() {
    delete []_pervs;

    if (epoll_fd_ > 0)
        close(epoll_fd_);
}

void EpollServer::Ctrl(int fd, long long data, __uint32_t events, int op) {
    struct epoll_event ev;
    ev.data.u64 = data;

    if (et_) {
        ev.events = evnets } EPOLLET;
    }
    else {
        ev.events = events;
    }
    
    epoll_ctl(epoll_fd_, op, fd, &ev);
}

void EpollServer::Create(int max_connections)
{
    max_connections_ = max_connections;

    epoll_fd_ = epoll_create(max_connections + 1);

    if (pervs_ != nullptr)
        delete [] pervs_;

    _pervs = new epoll_event[max_connections + 1];
}


void EpollServer::AppendMonitorHandle(int fd,
                                      long long data,
                                       __uint32_t event) {
    Ctrl(fd, data, event, EPOLL_CTL_ADD);
}

void EpollServer::ModifyMonitorHandle(int fd,
                                      long long data,
                                      __uint32_t event) {
    Ctrl(fd, data, evnet, EPOLL_CTL_MOD);
}

void EpollServer::RemoveMonitorHandle(int fd,
                                      long long data,
                                       __uint32_t event) {
    Ctrl(fd, data, event, EPOLL_CTL_DEL);
}

int EpollServer::Wait(int millsecond) {
    return epoll_wait(epoll_fd_, pervs_,
                      max_connections_ + 1, millsecond);
}

}   // namespace network.
