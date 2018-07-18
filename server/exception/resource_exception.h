//
// Created by Sunshine on 2018/7/18.
//

#ifndef TINYCHATSERVER_RESOURCEEXCEPTION_H
#define TINYCHATSERVER_RESOURCEEXCEPTION_H

#include <exception>

namespace mistake {

class resource_exception : std::exception {
 public:
    const char *what() const noexcept {
        return "Error! the sysytem thread is no enough.";
    }
};

}   // namespace mistake

#endif //TINYCHATSERVER_RESOURCEEXCEPTION_H
