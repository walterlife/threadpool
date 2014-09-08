/*
 * =========================================================================
 *
 *        Filename: Condition.hpp
 *
 *        Version:  1.0
 *        Complie:  gcc/g++
 *        Created:  2014-08-16 07:54:58
 *        Description: 条件变量封装类
 *
 *        Author:  walter(朱瑜玮) (walter@taomee.com)
 *        Company:  TaoMee.Inc, ShangHai.
 =========================================================================
*/

#include    "Mutex.hpp"

#include  <pthread.h>

namespace threadpool{

class Condition {
    public:
        explicit Condition(MutexLock&);
        ~Condition();
        void wait();
        void notify();
        void notify_all();
    private:
        MutexLock m_mutex;
        pthread_cond_t  m_cond;

};
}
