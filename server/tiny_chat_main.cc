//
// Created by Sunshine on 2018/7/18.
//
#include <iostream>

//#include "thread/tiny_chat_thread.h"
#include "thread/thread_pool.h"
#include "thread/base_task.h"
/*
class TestOne {
 public:
    virtual TestOne() = default;
    void Print() { std::cout << "this is TestOne function ."; }
};

class TestTo : public TestOne {

};

 */


int main(int argc, char* argv[]) {

    thread::ThreadInfo info;

    for (int i = 0; i < 100; i++) {
        info.name = i;
        info.id = thread::TinyChatThread::ThreadID::CLIENT_CONNECT_THREAD;
        thread::DefaultThreadPool::AllocateOneThread(info,
                                                     std::make_shared<thread::XTask>(),
                                                     nullptr);


        /*
        if (i == 10)
           return 0;
           */
    }

    //int a;

    //std::cin >> a;

    return 0;


}

