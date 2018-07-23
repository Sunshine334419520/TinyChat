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
              is_receive_(false),
              is_off_line_msg_(false){
        socket_ = network::ServerSocket::Create();
    }

    ~MessageImpl() {
        DestroyDelegate();
    }


    void SendMessage(network::Socket connfd) OVERRIDE {
        delegate_->SendMessage(connfd);
    }

    void ReceiveMessage(network::Socket connfd) OVERRIDE {
       assert(!delegate_ && !is_receive_);

        char buffer[constant::kNormalRecvBufLen];
        memset(buffer, 0, constant::kNormalRecvBufLen);

        socket_->Recv(connfd, buffer, constant::kNormalRecvBufLen);

        MessageStructBase* base_msg = static_cast<MessageStructBase*>(buffer);

       if (!InitDelegate(base_msg->type))
           return ;

       is_off_line_msg_ = CheckMessageStatus(base_msg->to);

       delegate_->ReceiveMessage(buffer);

       is_receive_ = true;
    }

    void ProcessMessage() OVERRIDE {
        if (is_receive_)
            throw mistake::message_exception("not receive to the message");

        delegate_->ProcessMessage(is_off_line_msg_);
    }

    void DestroyDelegate() noexcept OVERRIDE {
        delete delegate_;
        delegate_ = nullptr;
    }

    bool is_receive() const { return is_receive_; }
    bool is_off_line_msg() const { return is_off_line_msg_; }

 private:
    // 根据消息类型初始化delegate
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

    // 用来检查消息的状态，有两种状态，在线消息，和离线消息
    // 在线消息 true，离线消息 false.
    bool CheckMessageStatus(const char* to) {
        #if defined(TINYCHAT_SERVER)
        return true;
        #endif
    }

    Delegate* delegate_;         // 用来执行主要到工作
    bool is_receive_;           // true 表示接收到消息了
    bool is_off_line_msg_;

    #if defined(TINYCHAT_SERVER)
    // 一个socket 环境，不要在这个类调用Destroy(), 不然会导致外面的socket 环境失效;
    network::ServerSocket* socket_;
    #else
    network::ClientSOcket* socket_;
    #endif
};


}   // namesapce msg.
