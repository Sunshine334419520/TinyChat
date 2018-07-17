//
// Created by Sunshine on 2018/7/17.
//

#include "thread/tiny_chat_thread.h"


#include "thread/base_task.h"
#include "thread_pool.h"

namespace thread {

TinyChatThread::TinyChatThread(const std::string &name,
                               TinyChatThread::ThreadID id)
    : Thread(name), task_(nullptr), id_(id) {}

TinyChatThread::TinyChatThread(const std::string &name,
                               BaseTask* task,
                               TinyChatThread::ThreadID id)
    : Thread(name),
      task_(task),
      id_(id) {}

void TinyChatThread::Run() {

    while (task_ == nullptr)
        task_cond_.Wait();

    set_state(RUNNING);
    task_->Execute(task_data_);
}



}   // namespace thread