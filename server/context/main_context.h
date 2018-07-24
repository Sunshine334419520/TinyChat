//
// Created by Administrator on 2018/7/24 0024.
//

#ifndef TINYCHATSERVER_MAIN_CONTEXT_H
#define TINYCHATSERVER_MAIN_CONTEXT_H

#include "macor.h"
#include "network/server_socket.h"

namespace context {

class MainContext {
 public:
    MainContext() = default;

    // 创建一个上下文
    static MainContext *Create();

    // 获得当前运行环境
    static MainContext* GetCurrentContext();

    // 获得当前socket 句柄
    virtual network::Socket GetCurrentSocketfd(int tag) = 0;

    // 初始化环境
    virtual void Initialize() = 0;

    // 主要的执行内容
    virtual void Run() = 0;

    // 结束运行
    virtual void Shutdown() = 0;

    virtual bool is_running() const = 0;




 private:
 DISALLOW_COPY_AND_ASSIGN(MainContext);

};

}   // namespace context

#endif //TINYCHATSERVER_MAIN_CONTEXT_H
