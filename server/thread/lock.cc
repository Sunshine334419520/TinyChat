//
// Created by Sunshine on 2018/7/17.
//

#include "lock.h"

#include <cstdio>


namespace lock {

Mutex::Mutex() {
    if (pthread_mutex_init(&mutex_, nullptr) != 0)
       printf("mutex init error\n");
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&mutex_);
}

bool Mutex::mutex_lock() {
    return pthread_mutex_lock(&mutex_) == 0;
}

bool Mutex::mutex_unlock() {
    return pthread_mutex_unlock(&mutex_) == 0;
}

ConditionVariable::ConditionVariable() {
    if (pthread_mutex_init(&mutex_, nullptr) != 0)
        printf("mutex init error\n");

    if (pthread_cond_init(&cond_, nullptr) != 0) {
        pthread_mutex_destroy(&mutex_);
        printf("cond init error\n");
    }
}

ConditionVariable::~ConditionVariable() {
    pthread_mutex_destroy(&mutex_);
    pthread_cond_destroy(&cond_);
}

bool ConditionVariable::Wait() {
    int ans = 0;
    pthread_mutex_lock(&mutex_);
    ans = pthread_cond_wait(&cond_, &mutex_);
    pthread_mutex_unlock(&mutex_);

    return ans == 0;
}

bool ConditionVariable::Signal() {
    return pthread_cond_signal(&cond_) == 0;
}

bool ConditionVariable::BroadCast() {
    return pthread_cond_broadcast(&cond_);
}

RWLock::RWLock() {
    pthread_rwlock_init(&rw_lock_, nullptr);
}

RWLock::~RWLock() {
    pthread_rwlock_destroy(&rw_lock_);
}

bool RWLock::ReadLock() {
    return pthread_rwlock_rdlock(&rw_lock_) == 0;
}

bool RWLock::WriteLock() {
    return pthread_rwlock_wrlock(&rw_lock_) == 0;
}

bool RWLock::RWUnLock() {
    return pthread_rwlock_unlock(&rw_lock_) == 0;
}
}   // namespace lock
