//
// Created by Sunshine on 2018/7/18.
//
#include <iostream>

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

    for (int i = 0; i < 30; i++) {
        thread::DefaultThreadPool::AllocateOneThread(
                std::make_shared<thread::XTask>(), nullptr);
    }

    int a;

    std::cin >> a;

}

