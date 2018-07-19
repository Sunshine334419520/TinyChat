
# 支持的最低版本
cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0012 NEW)

#项目名称
project(TinyChatServer)

#支持C++11
add_definitions(-std=c++11)

include_directories(../server)

set(EXCEPTION_SRC exception/resource_exception.h
                  exception/resource_exception.cc)

set(THREAD_SRC  thread/thread.h
                thread/thread.cc
                thread/thread_pool.h
                thread/thread_pool.cc
                thread/lock.cc 
                thread/lock.h 
                thread/tiny_chat_thread.cc 
                thread/tiny_chat_thread.h 
                thread/base_task.h 
                )

set(NETWORK_SRC network/server_socket.cc
                network/server_socket.h)

set(MACOR_SRC macor.h)

set(MAIN_SRC tiny_chat_main.cc)


set(ALL_SRC ${EXCEPTION_SRC} ${THREAD_SRC} ${NETWORK_SRC} ${MACOR_SRC} ${MAIN_SRC})


#利用SRC生成一个可执行文件
add_executable(${PROJECT_NAME} ${ALL_SRC})
