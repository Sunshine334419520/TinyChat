//
// Created by Sunshine on 2018/7/16.
//

#include "thread.h"

#include <cassert>
#include <sched.h>


namespace thread {


Thread::Thread(const std::string& name)
    : name_(name),
      state_(NOCREATE),
      is_detach_(false),
      is_create_suspended_(false),
      priority_(-1) {

}


Thread::~Thread() {

}

void Thread::Terminate() {
    pthread_exit(NULL);
}

bool Thread::Start() {
    pthread_attr_t attr;
    sched_param param;

    pthread_attr_init(&attr);

    // Seting the detach of the thread.
    if (is_detach_)
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    // Set the priority.
    if (priority_ != -1) {

        pthread_attr_getschedparam(&attr, &param);
        param.sched_priority = priority_;
        pthread_attr_setschedparam(&attr, &param);
    }

    // Create the thread
    return pthread_create(&handle_, &attr, ThreadFunction, this) == 0;

}

bool Thread::WakeUp() {
    return false;
}

void *Thread::ThreadFunction(void * arg) {
    Thread* p_thread = (Thread*)(arg);

    p_thread->Run();
    return nullptr;
}


} // namespace thread

