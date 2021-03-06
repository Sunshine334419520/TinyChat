
# 支持的最低版本
cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0012 NEW)


#项目名称
project(TinyChatServer)

#支持C++11
add_definitions(-std=c++11)

include_directories(../server)

set(EXCEPTION_SRC exception/tiny_chat_exception.h
                  #exception/tiny_chat_exception.cc)
                    )



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

if (LINUX)
    set(NETWORK_SRC network/server_socket.cc
            network/server_socket.h
            network/client_socket.cc
            network/client_socket.h
            network/epoll_server.cc
            network/epoll_server.h)
elseif(APPLE)
    set(NETWORK_SRC network/server_socket.cc
            network/server_socket.h
            network/client_socket.cc
            network/client_socket.h
            )
elseif(WIN32)
    set(NETWORK_SRC #network/server_socket.cc
            #network/server_socket.h
            network/client_socket.cc
            network/client_socket.h
            )
else()
    set(NETWORK_SRC network/server_socket.cc
            network/server_socket.h
            network/client_socket.cc
            network/client_socket.h
            )
endif ()



set(MESSAGE_SRC message/message.h
                message/message.cc
                message/global_constant.h
                message/global_constant.cc)

set(CONTEXT_SRC context/main_context.cc
                context/main_context.h)

set(MACOR_SRC macor.h)

set(MAIN_SRC tiny_chat_main.cc)


set(ALL_SRC ${EXCEPTION_SRC} ${THREAD_SRC} ${NETWORK_SRC}
            ${MACOR_SRC} ${MAIN_SRC} ${MESSAGE_SRC} ${CONTEXT_SRC})

if(LINUX)
    target_link_libraries(${PROJECT_NAME} pthread)
endif()


#利用SRC生成一个可执行文件
add_executable(${PROJECT_NAME} ${ALL_SRC})
