/* Proj: cpp-functional-programming
 * File: lazy-value-basic-syntax.cc
 * Created Date: 2022/10/3
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/3 13:05:37
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <iostream>
#include <mutex>

template <typename F> class LazyValue
{
private:
    F function_; // value reference.
    mutable std::once_flag flag_;
    mutable decltype(function_()) cache_value_;

public:
    explicit LazyValue(F function)
        : function_(function)
    {
    }

    const decltype(cache_value_) &get() const
    {
        std::call_once(flag_, [this]() { cache_value_ = function_(); });
        return cache_value_;
    }
};

// 自动模版参数推断只用于函数模版
template <typename F> inline LazyValue<F> make_lazy_value(F &&function)
{
    return LazyValue<F>(std::forward<F>(function));
}

void test()
{
    auto res = [x = 10, y = 20] { return x + y; };
    std::cout << res() << std::endl;
}

void test2()
{
    const LazyValue lv = make_lazy_value([x = 10, y = 20]() { return x + y; });
    lv.get();
    std::cout << lv.get() << std::endl;
}

int main()
{
    // test();
    test2();
    return 0;
}
