//
// Created by Sunshine on 2018/7/17.
//

#ifndef TINYCHATSERVER_BASE_TASK_H
#define TINYCHATSERVER_BASE_TASK_H

namespace thread {

// 这是一个人物抽象类，继承它来，并且重写Execute method
// 实现自己所需要的任务
class BaseTask {
 public:
    BaseTask() noexcept = default;
    virtual ~BaseTask() = default;

    virtual void Execute(void* ptr) = 0;
};

}


#endif //TINYCHATSERVER_BASE_TASK_H
