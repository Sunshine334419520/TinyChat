//
// Created by Sunshine on 2018/7/16.
//

#include <pthread.h>

#include <string>

#ifndef TINYCHAT_THREAD_H
#define TINYCHAT_THREAD_H

namespace thread {

// 线程基类，对Unix系统级线程api进行类一套封装.
class Thread {
 public:


    // 线程的四种状态，空闲 忙碌 挂起 终止
    enum ThreadState {
        IDLE = 32,
        RUNNING,
        WAIT,
        EXIT,
        NOCREATE
    };


    // construct, destruct.
    explicit Thread(const std::string& name) noexcept;

    virtual ~Thread();

    // Run function
    // 这个函数是一个虚函数，继承Thread需要实现对应的线程运行方法
    virtual void Run() = 0;

    bool Start();                   // Start to execute the thread.
    bool WakeUp();                  // wake up the thread
    void Terminate();               // Terminate the thread.


    ThreadState  state() const { return state_; }
    std::string name() const { return name_; }
    //
    bool is_detach() const { return is_detach_; }
    bool is_create_suspended() const { return is_create_suspended_; }
    pthread_t handle() const { return handle_; }
    int priority() const { return priority_; }

    void set_state(ThreadState state) { state = state_; }
    void set_name(const std::string& name) { name_ = name; }

    void set_priority(int priority) { priority_ = priority;}


    bool Detach() {
        if (is_detach_) return false;

        is_detach_ = true;
        return is_detach_;
    }
    bool Join() {
        if (is_detach_) return false;
        pthread_join(handle_, nullptr);
    }                // Default behavior of the thread.

 protected:
    // 这个函数主要是用来执行动态调用，实现运行时多态
    static void* ThreadFunction(void*);


 private:
    std::string name_;                    // thread name
    ThreadState state_;             // thread state
    bool is_detach_;
    bool is_create_suspended_;
    int priority_;
    pthread_t handle_;              // POSIX C 线程实例


};

}

#endif //TINYCHAT_THREAD_H
