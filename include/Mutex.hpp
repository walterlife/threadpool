/*
 * =========================================================================
 *
 *        Filename: Mutex.hpp
 *
 *        Version:  1.0
 *        Complie:  gcc/g++
 *        Created:  2014-08-16 04:53:00
 *        Description:  互斥锁
 *
 *        Author:  walter(朱瑜玮) (walter@taomee.com)
 *        Company:  TaoMee.Inc, ShangHai.
 =========================================================================
*/

#ifndef  MUTEX_HPP
#define  MUTEX_HPP

#include    "Util.hpp"

#include  <pthread.h>

namespace threadpool{

    /**
     * @brief   互斥锁操作类
     *          封装了互斥锁的基本操作
     */
class MutexLock {
    public:
        explicit MutexLock();
        ~MutexLock();
        pthread_mutex_t& get_pthread_mutex() {
            return m_mutex;
        }
        void lock();
        void unlock();

    private:
        pthread_mutex_t m_mutex;
};


/**
 * @brief   互斥锁管理类
 *          管理互斥锁的加锁和解锁行为
 */
class AutoLockGuard {
    public:
        AutoLockGuard();
        explicit AutoLockGuard(MutexLock& mutexLock);
        ~AutoLockGuard();
    private:
        MutexLock m_mutexLock;
};

}

#endif  /*MUTEX_HPP*/
