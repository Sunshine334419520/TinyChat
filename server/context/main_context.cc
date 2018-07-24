//
// Created by Administrator on 2018/7/24 0024.
//

#include "main_context.h"


#include <cassert>
#include <cstring>

#include <iostream>
#include <memory>

#include "message/global_constant.h"
#include "thread/thread_pool.h"
#include "exception/tiny_chat_exception.h"



namespace context {



namespace {
MainContext* g_ContextInstance = nullptr;

}


struct Client {
    network::Socket fd;
    char name[constant::kUserNameMaxLen];
};

class MainContextImpl : public MainContext {
 public:
    MainContextImpl()
            :socket_(nullptr),
             client_(nullptr),
             is_initialize_(false),
             is_shutdown(false) {}

    network::Socket GetCurrentSocketfd(int tag) OVERRIDE {
       assert(is_running());
       client_rw_lock_.ReadLock();
       network::Socket i = client_[tag].fd;
       client_rw_lock_.RWUnLock();
       return i;
    }

    void Initialize() OVERRIDE {
        assert(!is_running());
        // 进行初始化工作
        socket_ = network::ServerSocket::Create();

        client_ = new Client[FD_SETSIZE];

        for (int i = 0; i < FD_SETSIZE; i++) {
            client_[i].fd = -1;
            strcpy(client_[i].name, "");
        }

        try {
            socket_->Listen();
        } catch(const mistake::socket_exception& s_ex) {
            std::cerr << "error_code : "<< s_ex.error_code() << "\t" <<
                      " error_info:" << s_ex.what() << std::endl;
            exit(s_ex.error_code());
        }

        is_initialize_ = true;

    }

    void Run() OVERRIDE {
        assert(is_initialize_);
        while (true) {
            try {
                network::Socket connfd = socket_->Accept();

                std::pair<bool, int> result = SetSocketfd(connfd);

                if (!result.first) {
                    std::cerr << "too many clients" << std::endl;
                }

                // 初始化info结构
                thread::ThreadInfo info;
                info.id = thread::TinyChatThread::ThreadID::CLIENT_CONNECT_THREAD;
                info.name = connfd;

                // 为客户端单独开辟一个线程
                thread::DefaultThreadPool::AllocateOneThread(info,
                                                             std::make_shared<thread::XTask>(),
                                                             (void*)result.second);

            } catch (const mistake::socket_exception& s_ex) {
                std::cerr << "error_code : " << s_ex.error_code() <<
                       "\t" << "error_info" << s_ex.what() << std::endl;
            }
        }
    }

    void Shutdown() OVERRIDE {
        assert(is_running());

        // 清理socket
        socket_->Destroy();

        // 清理client
        client_rw_lock_.WriteLock();
        delete client_;
        client_rw_lock_.RWUnLock();

        delete g_ContextInstance;
        g_ContextInstance = nullptr;

        exit(0);

    }


    bool is_running() const OVERRIDE {
        if (is_initialize_ && !is_shutdown)
            return true;
        return false;
    }

 private:
    std::pair<bool, int> SetSocketfd(network::Socket connfd) {
        client_rw_lock_.WriteLock();
        int i;
        for (i = 0; i < FD_SETSIZE; i++) {
            if (client_[i].fd < 0) {
                client_[i].fd = connfd;
                break;
            }
        }
        client_rw_lock_.RWUnLock();

        if (i == FD_SETSIZE)
            return std::make_pair(false, i);
        return std::make_pair(true, i);
    }

    network::ServerSocket* socket_;   // socket 环境
    Client* client_;                // 保存客户端基本信息
    bool is_initialize_;            // is initialize
    bool is_shutdown;               // is shutdown if true.

    //  保护client_ 数据 , unix 读写锁
    lock::RWLock client_rw_lock_;

};


MainContext *MainContext::Create() {
    if (!g_ContextInstance)
        g_ContextInstance = new MainContextImpl();
}


}   //namespace context