/**
 * @file noncopyable.h
 * @brief 不可拷贝对象封装
 * @author rock.yin
 * @email 564628276@qq.com
 * @date 2019-05-31
 * @copyright Copyright (c) 2019年 rock.yin All rights reserved (www.rock.top)
 */
#ifndef __ROCK_NONCOPYABLE_H__
#define __ROCK_NONCOPYABLE_H__

namespace rock {

/**
 * @brief 对象无法拷贝,赋值
 */
class Noncopyable {
public:
    /**
     * @brief 默认构造函数
     */
    Noncopyable() = default;

    /**
     * @brief 默认析构函数
     */
    ~Noncopyable() = default;

    /**
     * @brief 拷贝构造函数(禁用)
     */
    Noncopyable(const Noncopyable&) = delete;

    /**
     * @brief 赋值函数(禁用)
     */
    Noncopyable& operator=(const Noncopyable&) = delete;
};

}

#endif
