//
// Created by Sunshine on 2018/7/17.
//

#ifndef TINYCHATSERVER_TINY_CHAT_THREAD_H
#define TINYCHATSERVER_TINY_CHAT_THREAD_H


#include "thread.h"

#include <string>

#include "lock.h"

namespace thread {

class BaseTask;

class TinyChatThread : public Thread{
 public:

    enum ThreadID {
        DISPATCH_THREAD = 0,               // 调度线程
        CLIENT_THREAD,                     // 客户线程
        CLIENT_CONNECT_THREAD,             // 用来处理客户连接请求的线程
        CLIENT_MESSAGE_RECV_THREAD,        // 用来接收客户消息的线程
        CLIENT_MESSAGE_PROCESS_THREAD,     // 用来处理接收到客户消息的线程
        DEFAULT_THREAD                     // 默认线程
    };

    explicit TinyChatThread(const std::string& name,
                            ThreadID id = DEFAULT_THREAD);

    explicit TinyChatThread(const std::string& name,
                            BaseTask* task,
                            ThreadID id = DEFAULT_THREAD);
    ~TinyChatThread();

    // Thread method.
    void Run() override;

    void set_task(BaseTask* task, void* task_data);
    BaseTask* task() const { return task_; }

    ThreadID  id() const { return id_; }
    void set_id(ThreadID id) { id_ = id; }

 protected:
    lock::ConditionVariable task_cond_;
    lock::Mutex  work_mutex_;
 private:

    BaseTask* task_;            // 任务
    void* task_data_;           // 任务数据
    ThreadID id_;               // 线程的类型
};

}   // namespace thread


#endif //TINYCHATSERVER_TINY_CHAT_THREAD_H
