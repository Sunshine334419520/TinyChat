//
// Created by Sunshine on 2018/7/17.
//

#ifndef TINYCHATSERVER_THREAD_POOL_H
#define TINYCHATSERVER_THREAD_POOL_H

class ThreadQueue;

#include <cstddef>
#include <cassert>

#include <list>

#include "macor.h"
#include "thread/lock.h"
#include "thread/base_task.h"
#include "thread/tiny_chat_thread.h"
#include "exception/tiny_chat_exception.h"

namespace thread {

namespace {

const std::size_t kDefaultThMaxOfNum = 1024;
const std::size_t kDefaultInitOfNum = 20;
const std::size_t kDefaultIdleThMaxOfNum = 256;

}



class TinyChatThread;
class BaseTask;

// 这是一个线程池类，用来管理线程对分配以及多个线程对资源管理
// ThreadType : 需要管理的线程类型
// num_of_init : 初始化创建的线程个数
// for example : ThreadPool<WorkThread, 30> or ThreadPool<WorkThread>
template <class ThreadType, std::size_t num_of_init = 20>
class ThreadPool final {
    friend class TinyChatThread;
 public:
    typedef std::list<std::shared_ptr<ThreadType>> ThreadQueue;
    //typedef std::list<std::shared_ptr<ThreadType>> ThreadQueue;

 public:
    // 从线程池中取出一个线程，如果线程达到最大值,抛出异常
    static std::shared_ptr<ThreadType>
            AllocateOneThread(const ThreadInfo& info,
                              std::shared_ptr<BaseTask> task,
                              std::shared_ptr<void> data);

    // 结束所有的线程
    static void TerminateAll();

    static void set_num_of_max(std::size_t num_of_max) {
        num_of_mutex_.mutex_lock();
        num_of_max_ = num_of_max;
        num_of_mutex_.mutex_unlock();
    }

    static void set_num_of_max_idle(std::size_t num_of_max_idle) {
        num_of_mutex_.mutex_lock();
        num_of_max_idle_ = num_of_max_idle;
        num_of_mutex_.mutex_unlock();
    }

    static std::size_t num_of_max() {
        return num_of_max_;
    }
    static std::size_t num_of_max_idle() {
        return num_of_max_idle_;
    }
 private:

    // 启动线程池,在第一次调用AllocateOneThread时调用
    static void FirstStartUp();
    // 线程池数量不够，去申请新的线程
    static void ExtendNewThread(const int num);
    // 将空闲线程移动到忙碌线程
    static void MoveToBusyQueue(const std::shared_ptr<ThreadType>& );
    // 将忙碌线程移动到空闲线程
    static void MoveToIdleQueue(const std::shared_ptr<ThreadType>& );

    // 在idle thread 不够到时候调用此函数
    static void NotIdleThread();

    // 检查是否越界idle 并进行处理
    static void CheckAndProcessIdleCrossing();


    // 创建空闲线程, num 代表 create 个数
    static void AppendIdleThread(int num);
    // 删除num个空闲线程, discard function. not use.
    static void RemoveIdleThread(int num);
    static void RemoveBusyThread(int num);

    // Create a idle thread.
    static void AppendIdleThread() {
        AppendIdleThread(1);
    }

    /*
    // append a busy thread.
    static void AppendBusyThread() {
        AppendBusyThread(1);
    }
    */

    // Remove a idle thread.
    static void RemoveIdleThread() {
        RemoveIdleThread(1);
    }
    // Remove a busy thread.
    static void RemoveBusyThread() {
        RemoveBusyThread(1);
    }
 private:
    static bool is_first_use_;                  // 是不是首次使用线程池
    static std::size_t num_of_max_;            // 可以创建的最大线程数
    static std::size_t num_of_max_idle_;       // 可以拥有对最大空闲线程数
    static std::size_t num_of_current_;        // 当前的线程数

    static ThreadQueue thread_idle_queue_;            // 空闲线程队列
    static ThreadQueue thread_busy_queue_;            // 忙碌线程队列

    // Lock 为类线程队列
    static lock::Mutex num_current_mutex_;
    static lock::Mutex idle_mutex_;
    static lock::Mutex busy_mutex_;
    static lock::Mutex num_of_mutex_;
    static lock::Mutex is_first_mutex_;

    static lock::ConditionVariable idle_cond_;


 private:
    // 不允许实例化和继承
    DISALLOW_IMPLEMENT_AND_EXTEND(ThreadPool);



};

typedef ThreadPool<TinyChatThread, 20> DefaultThreadPool;


template <class T, std::size_t num>
bool ThreadPool<T, num>::is_first_use_ = true;

template <class T, std::size_t num>
std::size_t ThreadPool<T, num>::num_of_max_ = 1024;

template <class T, std::size_t num>
std::size_t ThreadPool<T, num>::num_of_max_idle_ = 64;

template <class T, std::size_t num>
std::size_t ThreadPool<T, num>::num_of_current_ = 0;

template <class T, std::size_t num>
typename ThreadPool<T, num>::ThreadQueue ThreadPool<T, num>::thread_idle_queue_;

template <class T, std::size_t num>
typename ThreadPool<T, num>::ThreadQueue ThreadPool<T, num>::thread_busy_queue_;

template <class ThreadType, size_t num_of_init>
lock::Mutex ThreadPool<ThreadType, num_of_init>::num_current_mutex_;

template <class ThreadType, size_t num_of_init>
lock::Mutex ThreadPool<ThreadType, num_of_init>::idle_mutex_;

template <class ThreadType, size_t num_of_init>
lock::Mutex ThreadPool<ThreadType, num_of_init>::busy_mutex_;

template <class ThreadType, size_t num_of_init>
lock::Mutex ThreadPool<ThreadType, num_of_init>::num_of_mutex_;

template <class ThreadType, size_t num_of_init>
lock::Mutex ThreadPool<ThreadType, num_of_init>::is_first_mutex_;

template <class ThreadType, size_t num_of_init>
lock::ConditionVariable ThreadPool<ThreadType, num_of_init>::idle_cond_;

template<class ThreadType, size_t num_of_init>
std::shared_ptr<ThreadType>
ThreadPool<ThreadType, num_of_init>::AllocateOneThread(const ThreadInfo& info,
                                                       std::shared_ptr<BaseTask> task,
                                                       std::shared_ptr<void> data) {
    // 第一次启动时需要跟线程池分配初始化线程.
    if (is_first_use_) {
        FirstStartUp();
        is_first_mutex_.mutex_lock();
        is_first_use_ = false;
        is_first_mutex_.mutex_unlock();
    }



    if (thread_idle_queue_.empty()) {       // 线程池中没有空闲线程
        NotIdleThread();
    }

    CheckAndProcessIdleCrossing();

    assert(!thread_idle_queue_.empty());
    assert(task);



    auto new_thread = thread_idle_queue_.front();


    new_thread->set_id(info.id);
    new_thread->set_name(info.name);
    new_thread->set_task(task, data);

    MoveToBusyQueue(new_thread);

    return new_thread;

}

template<class ThreadType, size_t num_of_init>
void ThreadPool<ThreadType, num_of_init>::TerminateAll() {
    if (!thread_busy_queue_.empty()) {
        throw mistake::terminate_exception();
    }

    RemoveIdleThread(thread_idle_queue_.size());
}

template<class ThreadType, size_t num_of_init>
void ThreadPool<ThreadType, num_of_init>::FirstStartUp() {
    AppendIdleThread(num_of_init);
}

template<class ThreadType, size_t num_of_init>
void ThreadPool<ThreadType, num_of_init>::ExtendNewThread(
        const int num) {
   AppendIdleThread(num);
}

template<class ThreadType, size_t num_of_init>
void ThreadPool<ThreadType, num_of_init>::MoveToBusyQueue(
        const std::shared_ptr<ThreadType> &need_move_thread) {
    // 移动Idle To Busy 其实就是添加busy，然后删除idle
    // 添加到busy
    busy_mutex_.mutex_lock();
    thread_busy_queue_.push_back(need_move_thread);
    busy_mutex_.mutex_unlock();

    // 删除idle
    idle_mutex_.mutex_lock();

    typename ThreadQueue::const_iterator it =
            thread_idle_queue_.begin();

    for ( ; it != thread_idle_queue_.end(); ++it) {
        if (*it == need_move_thread) {
            thread_idle_queue_.erase(it);
            break;
        }
    }

    idle_mutex_.mutex_unlock();
}

template<class ThreadType, size_t num_of_init>
void ThreadPool<ThreadType, num_of_init>::MoveToIdleQueue(
        const std::shared_ptr<ThreadType> &need_move_thread) {
        //ThreadType* need_move_thread) {
    // 参考MoveToBusyQueue
    idle_mutex_.mutex_lock();
    thread_idle_queue_.push_back(need_move_thread);
    idle_mutex_.mutex_unlock();



    busy_mutex_.mutex_lock();

    typename ThreadQueue::const_iterator it =
            thread_busy_queue_.begin();

    for ( ; it != thread_busy_queue_.end(); ++it) {
        if (*it == need_move_thread) {
            thread_busy_queue_.erase(it);
            break;
        }
    }

    busy_mutex_.mutex_unlock();


}

template<class ThreadType, size_t num_of_init>
void ThreadPool<ThreadType, num_of_init>::AppendIdleThread(int num) {
    assert(num >= 0);

    idle_mutex_.mutex_lock();
    for (int i = 0; i < num; i++) {
        // New thread and start this thread.
        auto new_thread = std::make_shared<ThreadType>("", nullptr, nullptr);
        thread_idle_queue_.push_back(new_thread);
        // 启动线程
        new_thread->Start();

        // 当前线程数加1
        num_current_mutex_.mutex_lock();
        ++num_of_current_;
        num_current_mutex_.mutex_unlock();
    }
    idle_mutex_.mutex_unlock();
}

template<class ThreadType, size_t num_of_init>
void ThreadPool<ThreadType, num_of_init>::RemoveIdleThread(int num) {
    idle_mutex_.mutex_lock();

    typename ThreadQueue::const_iterator it =
            thread_idle_queue_.begin();

    for ( ; it != thread_idle_queue_.end() && num > 0; ++it, --num) {
        (*it)->set_state(Thread::EXIT);
        thread_idle_queue_.erase(it);

        num_current_mutex_.mutex_lock();
        --num_of_current_;
        num_current_mutex_.mutex_unlock();
    }

    idle_mutex_.mutex_unlock();

}


template<class ThreadType, size_t num_of_init>
void ThreadPool<ThreadType, num_of_init>::RemoveBusyThread(int num) {

}

template<class ThreadType, size_t num_of_init>
void ThreadPool<ThreadType, num_of_init>::NotIdleThread() {

    if (num_of_current_ <= num_of_max_) {   // 还可以往线程池中添加线程
        // 计算需要扩充的线程数量
        const std::size_t extend_size =
                std::min(num_of_current_>>1, num_of_max_ - num_of_current_);
        ExtendNewThread(extend_size);
    }
    else {
        throw mistake::resource_exception();        // 线程数量不够，抛出异常， 客户端来进行处理，可以进行等待.
    }
}

template<class ThreadType, size_t num_of_init>
void ThreadPool<ThreadType, num_of_init>::CheckAndProcessIdleCrossing() {
    int idle_size = thread_idle_queue_.size();
    if (idle_size > num_of_max_idle_)
        RemoveIdleThread(idle_size - num_of_max_idle_);
}




} // namesapce thread


#endif //TINYCHATSERVER_THREAD_POOL_H
