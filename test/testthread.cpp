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

#include  <iostream>
#include  <cassert>
#include  <cstdlib>
#include  <cstdio>

using namespace threadpool;

void* func(void *arg)
{
    std::cout << "test thread class" << std::endl;
}

int main(int argc, char *argv[])
{
    threadpool::Thread thread(func);
    thread.startThread();
    thread.joinThread();
    return 0;
}
