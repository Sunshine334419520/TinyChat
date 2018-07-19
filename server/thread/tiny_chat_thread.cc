//
// Created by Sunshine on 2018/7/17.
//

#include "thread/tiny_chat_thread.h"

#include <iostream>

#include "thread/base_task.h"
#include "thread_pool.h"


namespace thread {

TinyChatThread::TinyChatThread(const std::string &name,
                               TinyChatThread::ThreadID id)
    : Thread(name), task_(nullptr), id_(id) {}

TinyChatThread::TinyChatThread(const std::string &name,
                               std::shared_ptr<BaseTask> task,
                               std::shared_ptr<void> task_data,
                               TinyChatThread::ThreadID id)
    : Thread(name),
      task_(task),
      task_data_(task_data),
      id_(id) {}

void TinyChatThread::Run() {

    std::shared_ptr<TinyChatThread> copy_this(this);

    for (;;) {

        while (task_ == nullptr  && state() == IDLE)
            task_cond_.Wait();

        // 设置state为 exit， 即可终止IDLE进程
        if (state() == EXIT)
            this->Terminate();

        set_state(RUNNING);
        task_->Execute(task_data_.get());
        //std::cout << name() << std::endl;
        //std::cout << std::endl;
        set_task(nullptr, nullptr);
        set_state(IDLE);


        DefaultThreadPool::MoveToIdleQueue(copy_this);
    }
}


void TinyChatThread::set_task(std::shared_ptr<BaseTask> task,
                              std::shared_ptr<void> task_data) {

    task_mutex_.mutex_lock();
    task_ = task;
    task_data_ = task_data;

    task_mutex_.mutex_unlock();
    task_cond_.Signal();
}




}   // namespace thread