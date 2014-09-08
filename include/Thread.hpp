/*
 * =========================================================================
 *
 *        Filename: Thread.hpp
 *
 *        Version:  1.0
 *        Complie:  gcc/g++
 *        Created:  2014-08-13 07:11:52
 *        Description:  线程处理基类
 *
 *        Author:  walter(朱瑜玮) (walter@taomee.com)
 *        Company:  TaoMee.Inc, ShangHai.
 =========================================================================
*/
#ifndef  THREAD_HPP
#define  THREAD_HPP

#include  <pthread.h>
#include  <functional>
#include  <iostream>

namespace threadpool{


enum ThreadState{
    RUN_STATE,
    JOIN_STATE
};
    /**
     * @brief   Thread 是线程基类
     *          封装了线程操作相关函数
     */
class Thread {

    public:
        /* 线程执行函数 */
        typedef std::function<void ()> ThreadFunc;
        /* 线程ID */
        typedef pthread_t   ThreadId;
        /* 线程属性初始化 */
        explicit Thread();        
        ~Thread();
        /* 启动线程 */
        void start_thread();
        /* 销毁线程 */
        int join_thread();
        /* 获得线程运行状态 */
        bool is_running() const {
            return (m_thread_state == RUN_STATE);
        }
        /* 获得线程的状态 */
        ThreadState get_state() const {
            return m_thread_state;
        }
        void set_state(ThreadState thread_state)
        {
            m_thread_state = thread_state;
        }
        /* 获得线程ID */
        ThreadId   get_thread_id() const {
            return m_thread_id;
        }

    public:
        ThreadId    m_thread_id;

    private:
        ThreadState m_thread_state;
        ThreadFunc  m_func_pointor;
};

} //namespace threadpool

#endif  /*THREAD_HPP*/
