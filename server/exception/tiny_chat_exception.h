//
// Created by Sunshine on 2018/7/18.
//

#ifndef TINYCHATSERVER_RESOURCEEXCEPTION_H
#define TINYCHATSERVER_RESOURCEEXCEPTION_H

#include <string>
#include <exception>

namespace mistake {

class resource_exception : std::exception {
 public:
    const char *what() const noexcept {
        return "Error! the sysytem thread is no enough.";
    }
};

class terminate_exception : std::exception {
 public:
    const char *what() const noexcept {
        return "Error! you still have unfinished threads. ";
    }
};

class socket_exception : std::exception {
 public:
    socket_exception(const std::string& str) const noexcept {
        error_str_ = str;
    }

    const char *what() const noexcept {
        return error_str_.c_str();
    }

 private:
   std::string error_str_;
};

}   // namespace mistake

#endif //TINYCHATSERVER_RESOURCEEXCEPTION_H
