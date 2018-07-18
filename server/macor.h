//
// Created by Sunshine on 2018/7/17.
//

#ifndef TINYCHATSERVER_MACOR_H
#define TINYCHATSERVER_MACOR_H

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




#endif //TINYCHATSERVER_MACOR_H
