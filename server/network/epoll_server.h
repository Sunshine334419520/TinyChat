//
// Created by Sunshine on 2018/7/20.
//

#ifndef TINYCHATSERVER_EPOLL_SERVER_H
#define TINYCHATSERVER_EPOLL_SERVER_H

#include <fchtl.h>
#include <sys/ioctl.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <sys/types.h>

#include "macor.h"

namespace network {


class EpollServer final {
 public:
    EpoolServer(bool b_et = true);

    ~EpoolServer();

    // 创建epoll， max_connections是服务需要支持的最大连接数
    void Create(int max_connections);

    // 添加监听事件
    // | fd | :  需要添加的句柄，比如socket，read， write 句柄.
    // | data| : 辅助的数据
    // | event| : 需要监听的事件 EPOLLIN |EPOLLOUT
    void AppendMonitorHandle(int fd, long long data, __uint32_t event);

    // 修改监听事件, 参数如上一个函数一样
    void ModifyMoniterHandle(int fd, long long data, __uint32_t event);

    // 删除正在监听的句柄
    void RemoveMoniterHandle(int fd, long long data, __uint32_t event);

    // | millsencond | 需要等待的毫秒
    int Wait(int millsencond);

    struct epoll_event& get(int i) {
         assert(pervs_ != 0);
         return perv_[i];
     }

 private:
    // 控制 epoll，将epoll设置为边缘触发EPOLLET模式
    // |fd| : epoll 句柄
    // |op| : EPOLL_CTL_ADD 注册新的fd到epfd中
    //        EPOLL_CTL_MOD 修改已经注册的fd的监听事件
    //        EPOLL_CTL_DEL 从epool fd 中删除一个fd
    void Ctrl(int fd, long long data, __uint32_t events, int op);

 private:
    int epoll_fd_;              // epoll
    int max_connections_;           // 最大连接数
    struct epoll_event* pervs_;         // 事件集

    bool is_et_;       //  是否是et模式

 private:
    DISALLOW_COPY_AND_ASSIGN(EpollServer);

};


}   // namespace network


#endif //TINYCHATSERVER_EPOOL_SERVER_H
