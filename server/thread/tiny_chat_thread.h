//
// Created by Sunshine on 2018/7/17.
//

#ifndef TINYCHATSERVER_TINY_CHAT_THREAD_H
#define TINYCHATSERVER_TINY_CHAT_THREAD_H


#include "thread.h"

#include <string>

#include "thread/lock.h"
#include "macor.h"
#include "base_task.h"


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

    TinyChatThread(const std::string& name,
                            std::shared_ptr<BaseTask> task,
                            std::shared_ptr<void> task_data,
                            ThreadID id = DEFAULT_THREAD);
    ~TinyChatThread() = default;

    // Thread method.
    void Run() OVERRIDE;

    void set_task(std::shared_ptr<BaseTask> task, std::shared_ptr<void> task_data);
    BaseTask* task() const { return task_.get(); }
    void* task_data() const { return task_data_.get(); }

    ThreadID  id() const { return id_; }
    void set_id(ThreadID id) { id_ = id; }

 protected:
    lock::ConditionVariable task_cond_;
    lock::Mutex  task_mutex_;
 private:

    std::shared_ptr<BaseTask> task_;            // 任务
    std::shared_ptr<void> task_data_;           // 任务数据
    ThreadID id_;               // 线程的类型
};

struct ThreadInfo {
    TinyChatThread::ThreadID id;
    std::string              name;

};

}   // namespace thread


#endif //TINYCHATSERVER_TINY_CHAT_THREAD_H
