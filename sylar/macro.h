/**
 * @file macro.h
 * @brief 常用宏的封装
 * @author rock.yin
 * @email 564628276@qq.com
 * @date 2019-06-01
 * @copyright Copyright (c) 2019年 rock.yin All rights reserved (www.rock.top)
 */
#ifndef __ROCK_MACRO_H__
#define __ROCK_MACRO_H__

#include <string.h>
#include <assert.h>
#include "log.h"
#include "util.h"

#if defined __GNUC__ || defined __llvm__
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率成立
#   define ROCK_LIKELY(x)       __builtin_expect(!!(x), 1)
/// LIKCLY 宏的封装, 告诉编译器优化,条件大概率不成立
#   define ROCK_UNLIKELY(x)     __builtin_expect(!!(x), 0)
#else
#   define ROCK_LIKELY(x)      (x)
#   define ROCK_UNLIKELY(x)      (x)
#endif

/// 断言宏封装
#define ROCK_ASSERT(x) \
    if(ROCK_UNLIKELY(!(x))) { \
        ROCK_LOG_ERROR(ROCK_LOG_ROOT()) << "ASSERTION: " #x \
            << "\nbacktrace:\n" \
            << rock::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

/// 断言宏封装
#define ROCK_ASSERT2(x, w) \
    if(ROCK_UNLIKELY(!(x))) { \
        ROCK_LOG_ERROR(ROCK_LOG_ROOT()) << "ASSERTION: " #x \
            << "\n" << w \
            << "\nbacktrace:\n" \
            << rock::BacktraceToString(100, 2, "    "); \
        assert(x); \
    }

#endif
