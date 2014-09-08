/*
 * =========================================================================
 *
 *        Filename: testthread.cpp
 *
 *        Version:  1.0
 *        Complie:  gcc/g++
 *        Created:  2014-08-16 02:46:24
 *        Description:  测试Thread类
 *
 *        Author:  walter(朱瑜玮) (walter@taomee.com)
 *        Company:  TaoMee.Inc, ShangHai.
 =========================================================================
*/

#include  "Thread.hpp"
#include  "ThreadPool.hpp"

#include  <iostream>
#include  <functional>
#include  <cassert>
#include  <unistd.h>
#include  <cstdlib>
#include  <cstdio>

using namespace threadpool;

void func()
{
    std::cout << "test thread class" << std::endl;
    pthread_exit((void*)(10));
}

int main(int argc, char *argv[])
{
    //auto f = std::bind(func, NULL);
    //threadpool::Thread thread(f)
    ThreadPool* pool = ThreadPool::create_instance();
    pool->do_init();
    pool->schedule(func);
    pool->schedule(func);
    pool->schedule(func);
    pool->schedule(func);
    //sleep(5);
    //pool->do_uninit();
    pool->stop_threads();
    return 0;
}
