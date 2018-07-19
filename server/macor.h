//
// Created by Sunshine on 2018/7/17.
//

#ifndef TINYCHATSERVER_MACOR_H
#define TINYCHATSERVER_MACOR_H

// 各个平台宏定义

#if !defined(OS_MACOS)

#define OS_MACOS __APPLE__ 

#endif


#if !defined(OS_LINUX)

#define OS_LINUX __linux

#endif

#if !defined(OS_WIN)

#define OS_WIN _WIN32

#endif

#if !defined(POSIX)

#define POSIX __posix




// 各个 C++ 基础宏定义
#if !defined(OVERRIDE)

#define OVERRIDE override

#endif


#if !defined(DISALLOW_COPY_ASSIGNMENT)

#define DISALLOW_COPY_ASSIGNMENT(Class_Name) \
 private:      \
 Class_Name(const Class_Name&);         \
 void operator=(const Class_Name&)

#endif

#if !defined(DISALLOW_IMPLEMENT_AND_EXTEND)

#define DISALLOW_IMPLEMENT_AND_EXTEND(Class_Name) \
  Class_Name();         \
  ~Class_Name();            \
  DISALLOW_COPY_ASSIGNMENT(Class_Name)

#endif

#if !defined(DISALLOW_IMPLEMENT)

#define DISALLOW_IMPLEMENT(Class_Name) \
 protected:              \
  Class_Name();          \
  ~Class_Name();           \
  DISALLOW_COPY_ASSIGNMENT(Class_Name)

#endif

#if !defined(ALLOW_ONLY_HEAP_ALLOC)

#define ONLYALLOW_HEAP_ALLOC_AND_NOTEXTEND(Class_Name)   \
 private:         \
  ~Class_Name() {}

#endif

#define ONLYALLOW_HEAP_ALLOC(Class_Name)          \
 protected:
  virtual ~Class_Name() {}





#endif //TINYCHATSERVER_MACOR_H
