
# 支持的最低版本
cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0012 NEW)

#项目名称
project(TinyChatServer)

#支持C++11
add_definitions(-std=c++11)

include_directories(../server)

#设置SRC变量
set(SRC thread/thread.h
        thread/thread.cc
        thread/thread_pool.h
        thread/thread_pool.cc macor.h thread/lock.cc thread/lock.h thread/tiny_chat_thread.cc thread/tiny_chat_thread.h thread/base_task.h)
#利用SRC生成一个可执行文件
add_executable(${PROJECT_NAME} ${SRC})
