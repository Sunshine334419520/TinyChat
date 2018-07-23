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
    explicit socket_exception(const std::string& str) const noexcept
        : error_code_(0), error_str_(str){
    }

    explicit socket_exception(int error_code) const noexcept
        : error_code_(error_code), error_str_("socket error"){
    }

    socket_exception(int error_code, const std::string& str) const noexcept
        : error_code_(error_code), error_str_(str) {}

    const char *what() const noexcept {
        return error_str_.c_str();
    }

    int error_code() const { return error_code_; }

 private:
   int error_code_;
   std::string error_str_;
};


class message_exception : std::exception {
 public:
    explicit message_exception(const std::string& str) const noexcept
        : error_str_(str) {}

    const char *what() const noexcept {
        return error_str_.c_str();
    }

 private:
    std::string error_str_;
};

}   // namespace mistake

#endif //TINYCHATSERVER_RESOURCEEXCEPTION_H
