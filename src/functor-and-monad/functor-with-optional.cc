/* Proj: cpp-functional-programming
 * File: functor-with-optional.cc
 * Created Date: 2022/10/9
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/9 13:24:37
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <iostream>
#include <optional>
#include <future>

template <typename T, typename F> auto transform(std::optional<T> opt, F f)
    -> decltype(std::make_optional(f(opt.value())))
{
    if (opt) {
        return std::make_optional(f(opt.value()));
    } else {
        return {};
    }
}

void test()
{
    auto opt = transform(std::make_optional<std::string>("Hello"),
                         [](std::string &value) { return value + " world"; });
    if (opt) std::cout << opt.value() << std::endl;
}

int main()
{
    test();
    return 0;
}
