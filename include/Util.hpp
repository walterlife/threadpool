/*
 * =========================================================================
 *
 *        Filename: Util.hpp
 *
 *        Version:  1.0
 *        Complie:  gcc/g++
 *        Created:  2014-08-16 06:15:13
 *        Description:  基础操作集合
 *
 *        Author:  walter(朱瑜玮) (walter@taomee.com)
 *        Company:  TaoMee.Inc, ShangHai.
 =========================================================================
*/

#ifndef  UTIL_HPP
#define  UTIL_HPP

#ifdef likely
#undef likely
#endif
#define likely(x) __builtin_expect((!!x), 1)

#ifdef unlikely
#undef unlikely
#endif
#define unlikely(x) __builtin_expect((!!x), 0)


#endif  /*UTIL_HPP*/
