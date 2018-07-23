//
// Created by Sunshine on 2018/7/23.
//

#ifndef TINYCHATSERVER_GLOBAL_CONSTANT_H
#define TINYCHATSERVER_GLOBAL_CONSTANT_H

namespace constant {

extern const int kUserNameMaxLen;     // 用户名的最大长度
extern const int kPasswordMaxLen;     // 密码的最大长度
extern const int kNormalRecvBufLen;     // 普通消息给4字节接收缓冲区
extern const int kLargeRecvBufLen;      // 大数据

}

#endif //TINYCHATSERVER_GLOBAL_CONSTANT_H


