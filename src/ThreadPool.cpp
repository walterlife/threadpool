/*
 * =========================================================================
 *
 *        Filename: ThreadPool.cpp
 *
 *        Version:  1.0
 *        Complie:  gcc/g++
 *        Created:  2014-08-23 07:56:09
 *        Description:  线程池类
 *
 *        Author:  walter(朱瑜玮) (walter@taomee.com)
 *        Company:  TaoMee.Inc, ShangHai.
 =========================================================================
*/

#include  "ThreadPool.hpp"

#include  <cassert>
#include  <iostream>
#include  <iterator>
namespace threadpool{

ThreadPool* ThreadPool::m_instance= NULL;
MutexLock   ThreadPool::m_pool_mutex;
/**
* @brief   ThreadPool 
*          够找函数
* @param   thread_size
*/
ThreadPool::ThreadPool(uint32_t thread_size)
    : m_not_full_cond(m_task_mutex),
      m_is_running(false),    
      m_not_empty_cond(m_task_mutex)
{
    if( thread_size < MIN_THREAD_SIZE ){
        m_thread_size = MIN_THREAD_SIZE;
    } else if( thread_size > MAX_THREAD_SIZE ){
        m_thread_size= MAX_THREAD_SIZE;
    } else  {
        m_thread_size = thread_size;
    }
    m_initital = false;
    m_thread_list.empty();
}

/**
 * @brief   ~ThreadPool 析构函数
 */
ThreadPool::~ThreadPool()
{
    do_uninit();
}

/**
* @brief   create_instance 
*          创建/获得线程池实例 
*  双重判断，线程安全
* @return  
*/
ThreadPool* ThreadPool::create_instance()
{
    if( NULL == m_instance ){
        AutoLockGuard lock(m_pool_mutex);
        if( NULL == m_instance ){
            m_instance = new ThreadPool(MIN_THREAD_SIZE); 
        }
    }
    return m_instance;
}

/**
 * @brief   do_init 初始化线程池
 *
 * @return  
 */
bool ThreadPool::do_init()
{
    if( m_initital ){
        return true;
    }
    if( !start_threads() ){
        return false;
    }
    m_is_running = true;
    m_initital= true;
    return true;
}

/**
 * @brief   start_threads 创建线程池所有线程
 */
bool ThreadPool::start_threads()
{
    if( !m_thread_list.empty() ){
        return true;
    }
    m_thread_list.reserve(m_thread_size);
    
    Thread* thread = NULL;
    for( int i = 0 ; i < m_thread_size ; i++ )
    {
        thread = new Thread();
        /* 创建线程 */
        if (pthread_create(&thread->m_thread_id, NULL, ThreadPool::thread_func, static_cast<void*>(thread)))
        {
            delete thread;
            thread = NULL;
            continue;
        }
        m_thread_list.push_back(thread);
    }
    return true;
}


/**
 * @brief   thread_func 
 *          线程执行函数
 * @param   arg  线程实例
 *
 * @return  
 */
void* ThreadPool::thread_func(void *arg)
{
    ThreadPool* pool = ThreadPool::create_instance();
    Thread* thread = static_cast<Thread*>(arg);
    threadpool::Thread::ThreadId self_id = thread->get_thread_id();
    std::cout << "111111\n";
    //std::cout << pool->is_running() << std::endl;
    while (pool->is_running())
    {
        std::cout << "execute 1111" << std::endl;
        Task task = pool->take_task();
        if (task)
        {
            task();
        }
    }
    return static_cast<void*>(0);
}

/**
 * @brief   schedule 
 *          添加任务
 * @param   task
 */
void ThreadPool::schedule(const Task& task)
{
    /* 没有线程 */
    if( m_thread_list.empty() ){
        task();
    } else {
        AutoLockGuard lock(m_task_mutex); 
        /* 任务数量超过上限 */
        while( is_task_full() ){
            /* 等到任务队列不满 */
            m_not_full_cond.wait();
        }
        if( !is_task_full() ){
            /* 将任务放到任务队列里 */
            m_task_list.push_front(task);
            /* 通知所有线程任务到来 */
            m_not_empty_cond.notify(); 
        }
    }
}

/**
 * @brief   take_task 
 *          获得一个任务
 * @return  
 */
ThreadPool::Task& ThreadPool::take_task()
{
    AutoLockGuard lock(m_task_mutex);
    while( m_task_list.empty() && m_is_running){
        std::cout << "Here\n";
        m_not_empty_cond.wait();
    }
    Task task;
    if( !m_task_list.empty() ){
        task = m_task_list.front();
        m_task_list.pop_front();
        m_not_full_cond.notify();
    }
    return task;
}

/**
 * @brief   is_task_full 
 *          判断任务队列是否已满
 * @return  
 */
bool ThreadPool::is_task_full() const
{
    std::cout << "Here " << (!m_task_list.empty() && m_task_list.size() > MAX_TASK_SIZE) << std::endl;
    return (!m_task_list.empty() && m_task_list.size() > MAX_TASK_SIZE);      
}

/**
 * @brief   stop_threads 
 *          销毁线程池中线程的资源
 */
void ThreadPool::stop_threads()
{
    /* 通知线程池线成完成还未完成的任务 */
    {
        AutoLockGuard lock(m_task_mutex);
        //m_is_running= false;
        m_not_empty_cond.notify_all();
    }
    /* 后续改成使用 c++0x */
    //for_each(m_thread_list.begin()
             //m_thread_list.end(),
             //std::function(Thread::join_thread), _1);
    std::vector<Thread*>::iterator it = m_thread_list.begin();
    for( ; it != m_thread_list.end() ; it++ ){
        Thread* thread = *it;
        thread->join_thread();
        delete thread;
    } 
    m_thread_list.clear();
    m_task_list.empty();
}

void ThreadPool::do_uninit()
{
    if (m_is_running)
    {
        stop_threads();
    }
}
}
