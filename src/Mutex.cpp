/*
 * =========================================================================
 *
 *        Filename: MutexLock.cpp
 *
 *        Version:  1.0
 *        Complie:  gcc/g++
 *        Created:  2014-08-16 06:34:35
 *        Description:  互斥锁类
 *
 *        Author:  walter(朱瑜玮) (walter@taomee.com)
 *        Company:  TaoMee.Inc, ShangHai.
 =========================================================================
*/

#include  "Mutex.hpp"

#include  <cstdlib>
#include  <iostream>

namespace threadpool{
    
MutexLock::MutexLock()
{
    if (likely(pthread_mutex_init(&m_mutex,NULL) != 0))
    {
        std::cout << "mutex init failed\n";
        exit(10);
    }
}

MutexLock::~MutexLock()
{
   if (likely(pthread_mutex_destroy(&m_mutex) != 0))
   {
       std::cout << "mutex destroy failed\n";
       exit(10);
   }
}

void MutexLock::lock()
{
    if(likely(pthread_mutex_lock(&m_mutex) != 0 ))
    {
        std::cout << "mutex lock failed\n";
        exit(10);
    }
}

void MutexLock::unlock()
{
    if (likely(pthread_mutex_unlock(&m_mutex) != 0))
    {
        std::cout << "mutex unlock failded\n";
        exit(10);
    }
}

AutoLockGuard::AutoLockGuard(MutexLock& mutexLock)
    : m_mutexLock(mutexLock)
{
    m_mutexLock.lock();
}

AutoLockGuard::~AutoLockGuard()
{
    m_mutexLock.unlock();
}

} //namespace threadpool
