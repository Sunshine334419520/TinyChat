//
// Created by Sunshine on 2018/7/22.
//
#include "message.h"

#include <cassert>

#include "exception/tiny_chat_exception.h"

namespace msg {

// Message 类的实例化类
class MessageImpl : public Message {
 public:
    MessageImpl()
            : delegate_(nullptr),
              is_receive_(false) {}


    void SendMessage(network::Socket connfd) OVERRIDE {
        delegate_->SendMessage(connfd);
    }

    void ReceiveMessage(network::Socket connfd) OVERRIDE {
       assert(!delegate_ && !is_receive_);

        char buffer[constant::kNormalRecvBufLen];
        memset(buffer, 0, constant::kNormalRecvBufLen);

        socket_->Recv(connfd, buffer, constant::kNormalRecvBufLen);

       if (!InitDelegate(static_cast<MessageStructBase*>(buffer)->type))
           return ;

       delegate_->ReceiveMessage(nullptr);

       is_receive_ = true;
    }

    void ProcessMessage() OVERRIDE {
        if (is_receive_)
            throw mistake::message_exception("not receive to the message");

        delegate_->ProcessMessage();
    }

    void DestroyDelegate() noexcept OVERRIDE {
        delete delegate_;
        delegate_ = nullptr;
    }

    bool is_receive() const { return is_receive_; }

 private:
    bool InitDelegate(MsgType msg_type) {
        switch(msg_type) {
            case MsgType::IS_LOGIN:
            case MsgType::IS_REGISTER:
            case MsgType::IS_LOGOUT:
            {
                delegate_ = CreateLoginDelegate();
                break;
            }
            case MsgType::IS_ADD_FRIEND:
            case MsgType::IS_DEL_FRIEND:
            {
                delegate_ = CreateRequestToFriendDelegate();
                break;
            }
            case MsgType::IS_ADD_GROUP:
            case MsgType::IS_DEL_GROUP:
            {
                delegate_ = CreateRequestToGroupDelegate();
                break;
            }
            case MsgType::IS_FRIEND_VERIFY:
            case MsgType::IS_GROUP_VERIFY:
            {
                delegate_ = CreateVerifyDelegate();
                break;
            }
            case MsgType::IS_FRIEND_VERIFY_REPLY:
            case MsgType::IS_GROUP_VERIFY_REPLY:
            {
                delegate_ = CreateReplyDelegate();
                break;
            }
            case MsgType::IS_PUBLIC_CHAT:
            case MsgType::IS_PRIVATE_CHAT:
            {
                delegate_ = CreateChatDelegate();
                break;
            }
            default:
                return false;
        }

        return true;
    }

    Delegate* delegate_;         // 用来执行主要到工作
    bool is_receive_;           // true 表示接收到消息了

    #if defined(TINYCHAT_SERVER)
    // 一个socket 环境，不要在这个类调用Destroy(), 不然会导致外面的socket 环境失效;
    network::ServerSocket* socket_;
    #else
    network::ClientSOcket* socket_;
    #endif
};


}   // namesapce msg.
