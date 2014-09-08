/*
 * =========================================================================
 *
 *        Filename: Condition.cpp
 *
 *        Version:  1.0
 *        Complie:  gcc/g++
 *        Created:  2014-08-16 08:06:16
 *        Description:  条件变量封装类
 *
 *        Author:  walter(朱瑜玮) (walter@taomee.com)
 *        Company:  TaoMee.Inc, ShangHai.
 =========================================================================
*/

#include  "Condition.hpp"

#include  <iostream>
#include  <cstdlib>

namespace threadpool{
    
Condition::Condition(MutexLock& mutex)
    :m_mutex(mutex)
{
    if (likely(pthread_cond_init(&m_cond, NULL) != 0))
    {
        std::cout<< "condition init failed\n";
        exit(10);
    }
}

Condition::~Condition()
{
    if (likely(pthread_cond_destroy(&m_cond) != 0))
    {
        std::cout << "condition destroy failed\n";
        exit(10);
    }
}

void Condition::wait()
{
    if (likely(pthread_cond_wait(&m_cond, &m_mutex.get_pthread_mutex()) != 0))
    {
        std::cout << "wait condition falied\n";
        exit(10);
    }
}

void Condition::notify()
{
    if (likely(pthread_cond_signal(&m_cond) != 0))
    {
        std::cout << "condition signal failed\n";
        exit(10);
    }
}

void Condition::notify_all()
{
    if (likely(pthread_cond_broadcast(&m_cond) != 0))
    {
        std::cout << "condition broadcast failed\n";
        exit(10);
    }
}

} //namespace threadpool
