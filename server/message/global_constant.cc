//
// Created by Sunshine on 2018/7/23.
//

#include "global_constant.h"


namespace constant {

const int kUserNameMaxLen = 32;     // 用户名的最大长度
const int kPasswordMaxLen = 64;     // 密码的最大长度
const int kNormalRecvBufLen = 4 * 1024;     // 普通消息给4字节接收缓冲区
const int kLargeRecvBufLen = 8 * 1024;      // 大数据

}
