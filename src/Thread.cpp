/*
 * =========================================================================
 *
 *        Filename: Thread.cpp
 *
 *        Version:  1.0
 *        Complie:  gcc/g++
 *        Created:  2014-08-15 23:30:29
 *        Description:  线程基础类
 *
 *        Author:  walter(朱瑜玮) (walter@taomee.com)
 *        Company:  TaoMee.Inc, ShangHai.
 =========================================================================
*/

#include  "Thread.hpp"
#include  "Util.hpp"

#include  <cassert>
#include  <cstdio>
#include  <cstdlib>
#include  <iostream>

namespace threadpool{

Thread::Thread()
    : m_thread_state(RUN_STATE),
    m_thread_id(0)
{

}

Thread::~Thread()
{
    if (m_thread_state == RUN_STATE)
    {
        /* 若线程join 失败 or 没有join 则调用该函数释放线程资源 */
        pthread_detach(m_thread_id);
    }
}

void Thread::start_thread()
{
    //assert(!m_is_started);
    //m_is_started = true;
    ///* 启动线程 */
    //if(likely(pthread_create(&m_thread_id,NULL,m_func_pointor,NULL)!=0))
    //{
        //m_is_started = false;
        //std::cout << "start thread failed" << std::endl;
        //exit(10);
    //}
}

int Thread::join_thread()
{
    assert(m_thread_state == RUN_STATE);
    m_thread_state = JOIN_STATE;
    if (likely(pthread_join(m_thread_id, NULL) != 0))
    {
        m_thread_state = RUN_STATE;
        std::cout << "join thread failed" << std::endl;
        exit(10);
    }
    return 0;
}

} //namespace threadpool
