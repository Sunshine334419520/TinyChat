//
// Created by Sunshine on 2018/7/17.
//

#ifndef TINYCHATSERVER_LOCK_H
#define TINYCHATSERVER_LOCK_H

#include <pthread.h>

namespace lock {

// mutex loacker
class Mutex final {
 public:
    Mutex();
    ~Mutex();
    bool mutex_lock();
    bool mutex_unlock();

 private:
    pthread_mutex_t mutex_;
};

class ConditionVariable final {
 public:
    ConditionVariable();
    ~ConditionVariable();

    // 等待条件变量
    bool Wait();
    // 唤醒等待条件变量的线程
    bool Signal();
    // 唤醒所有等待条件变量的线程
    bool BroadCast();

 private:
    pthread_mutex_t mutex_;
    pthread_cond_t cond_;
};

}


#endif //TINYCHATSERVER_LOCK_H
