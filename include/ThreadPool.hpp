/*
 * =========================================================================
 *
 *        Filename: ThreadPoll.hpp
 *
 *        Version:  1.0
 *        Complie:  gcc/g++
 *        Created:  2014-08-16 03:16:17
 *        Description:  线程池类
 *
 *        Author:  walter(朱瑜玮) (walter@taomee.com)
 *        Company:  TaoMee.Inc, ShangHai.
 =========================================================================
*/

#ifndef  THREADPOLL_HPP
#define  THREADPOLL_HPP

#include  "Thread.hpp"
#include  "Condition.hpp"
#include  "Mutex.hpp"

#include  <vector>
#include  <functional>
#include  <deque>
#include  <iostream>
#include  <cstdint>

namespace threadpool{

/* 最大线程个数 */
const uint8_t  MAX_THREAD_SIZE = 20;
/* 最小线程个数 */
const uint8_t  MIN_THREAD_SIZE = 4;
/* 最大处理的任务个数，该值可调 */
const uint32_t  MAX_TASK_SIZE = 10000;
    /**
     * @brief   线程池类
     */
class ThreadPool {
    /* 线程处理函数,可以是业务层接口函数*/
    typedef std::function<void ()> Task;

    public:
        explicit ThreadPool(uint32_t thread_size);
        bool    do_init();
        void    do_uninit();
        static ThreadPool* create_instance();
        ~ThreadPool();
        bool start_threads();
        void stop_threads();
        /* 接受上层函数 */
        void schedule(const Task&);
        bool is_task_full() const;
        bool is_running() const {
            return m_is_running;
        }
        Task& take_task();
        /* 线程处理函数 */
        static void*   thread_func(void* arg);

    private:
        /* 线程池状态 */
        uint32_t                m_is_running;
        /* 线程池有的线程数目 */
        uint32_t                m_thread_size;
        /* 线程队列 */
        std::vector<Thread*>    m_thread_list;
        /* 任务队列 */
        std::deque<Task>        m_task_list;
        /* 有任务条件变量 */
        Condition               m_not_full_cond;
        /* 没有任务条件变量 */
        Condition               m_not_empty_cond;
        /* 互斥取/存任务 */
        MutexLock               m_task_mutex;
        static MutexLock        m_pool_mutex;

        /* 线程池实例 */
        static ThreadPool*      m_instance;
        bool                    m_initital;
};
}

#endif  /*THREADPOLL_HPP*/
