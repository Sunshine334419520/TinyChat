//
// Created by Sunshine on 2018/7/17.
//

#ifndef TINYCHATSERVER_THREAD_POOL_H
#define TINYCHATSERVER_THREAD_POOL_H

#include <cstddef>

#include <queue>

#include "macor.h"
#include "thread/lock.h"
#include "thread/base_task.h"
#include "thread/tiny_chat_thread.h"

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
    friend ThreadType;
 public:
    typedef std::queue<std::shared_ptr<ThreadType>> ThreadQueue;

 public:
    // 从线程池中取出一个线程，如果线程达到最大值,抛出异常
    TinyChatThread* AllocateOneThread(BaseTask* task, void* data);

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
    static bool ExtendNewThread(const std::size_t num);
    // 将空闲线程移动到忙碌线程
    static void MoveToBusyQueue(const std::shared_ptr<ThreadType>& thread_idle);
    // 将忙碌线程移动到空闲线程
    static void MoveToIdleQueue(const std::shared_ptr<ThreadType>& thread_idle);


    // 创建空闲线程, num 代表 create 个数
    static void CreateIdleThread(int num);
    // 删除num个空闲线程
    static void RemoveIdleThread(int num);
    static void RemoveBusyThread(int num);

    // Create a idle thread.
    static void CreateIdleThread() {
        CreateIdleThread(1);
    }

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
    static lock::Mutex idle_mutex_;
    static lock::Mutex busy_mutex_;
    static lock::Mutex num_of_mutex_;
    static lock::Mutex is_first_mutex_;

    static lock::ConditionVariable idle_cond_;


 private:
    // 不允许实例化和继承
    DISALLOW_IMPLEMENT_AND_EXTEND(ThreadPool);



};


template <class T, std::size_t num>
bool ThreadPool<T, num>::is_first_use_ = true;

template <class T, std::size_t num>
std::size_t ThreadPool<T, num>::num_of_max_ = 1024;

template <class T, std::size_t num>
std::size_t ThreadPool<T, num>::num_of_max_idle_ = 256;

template<class ThreadType, size_t num_of_init>
TinyChatThread *
ThreadPool<ThreadType, num_of_init>::AllocateOneThread(BaseTask* task,
                                                       void* data) {
    // 第一次启动时需要跟线程池分配初始化线程.
    if (is_first_use_) {
        FirstStartUp();
        is_first_mutex_.mutex_lock();
        is_first_use_ = false;
        is_first_mutex_.mutex_unlock();
    }

    if (thread_idle_queue_.empty()) {       // 线程池中没有空闲线程
        if (num_of_current_ <= num_of_max_) {   // 还可以往线程池中添加线程
            // 计算需要扩充的线程数量
            const std::size_t extend_size =
                    std::min(num_of_current_>>1, num_of_max_ - num_of_current_);
            ExtendNewThread(extend_size);
        }
        else {
            throw 0;        // 线程数量不够，抛出异常， 客户端来进行处理，可以进行等待.
        }
    }
}



} // namesapce thread


#endif //TINYCHATSERVER_THREAD_POOL_H
