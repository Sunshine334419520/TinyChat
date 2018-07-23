//
// Created by Sunshine on 2018/7/21.
//

#ifndef TINYCHATSERVER_MESSAGE_H
#define TINYCHATSERVER_MESSAGE_H

#include "macor.h"
#include "global_constant.h"

#if defined(TINYCHAT_SERVER)
#include "network/server_socket.h"
#endif

#if defined(TINYCHAT_CLIENT)
#include "network/client_socket.h"
#endif

namespace msg {


// 消息类型

enum class MsgType {
    IS_LOGIN = 0x123456,
    IS_REGISTER,
    IS_LOGOUT,
    IS_PUBLIC_CHAT,
    IS_PRIVATE_CHAT,
    IS_ADD_FRIEND,
    IS_DEL_FRIEND,
    IS_ADD_GROUP,
    IS_DEL_GROUP,
    IS_FRIEND_VERIFY,
    IS_GROUP_VERIFY,
    IS_FRIEND_VERIFY_REPLY,
    IS_GROUP_VERIFY_REPLY
};

// 基础消息信息
struct MessageStructBase {
    MsgType type;
    const char from[constant::kUserNameMaxLen];
    const char to[constant::kUserNameMaxLen];
};

class Message {
 public:
    Message() = default;
    virtual ~Message() = default;

    class Delegate {
     public:
        virtual ~Delegate() = default;

        virtual void SendMessage(network::Socket conndf) = 0;

        virtual void ReceiveMessage(const char*) = 0;

        virtual void ProcessMessage() = 0;

     private:
        DISALLOW_COPY_AND_ASSIGN(Delegate);
    };

    template <class MessageStruct>
    static void SendMessage(network::Socket connfd,
                            const MessageStruct& send_info);


    virtual void SendMessage(network::Socket connfd) = 0;

    virtual void ReceiveMessage(network::Socket connfd) = 0;

    virtual void ProcessMessage() = 0;

    virtual void DestroyDelegate() noexcept = 0;



 private:
    DISALLOW_COPY_AND_ASSIGN(Message);
};

template<class MessageStruct>
void Message::SendMessage(network::Socket connfd,
                          const MessageStruct &send_info) {

}


}   // namespace msg.

#endif //TINYCHATSERVER_MESSAGE_H
