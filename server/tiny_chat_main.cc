//
// Created by Sunshine on 2018/7/18.
//
#include <iostream>

#include "thread/thread_pool.h"
#include "thread/base_task.h"



int main(int argc, char* argv[]) {

    thread::ThreadInfo info;

    for (int i = 0; i < 100; i++) {
        info.name = i;
        info.id = thread::TinyChatThread::ThreadID::CLIENT_CONNECT_THREAD;
        thread::DefaultThreadPool::AllocateOneThread(info,
                                                     std::make_shared<thread::XTask>(),
                                                     nullptr);

    }



    return 0;


}

