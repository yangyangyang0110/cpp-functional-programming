/* Proj: cpp-functional-programming
 * File: pattern-match.cc
 * Created Date: 2022/10/7
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/7 19:00:41
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <iostream>
#include <type_traits>

template <typename T1, typename T2> struct is_same : std::false_type {
};

template <typename T> struct is_same<T, T> : std::true_type {
};

void test() { static_assert(is_same<int, int>::value); }

int main()
{
    test();
    return 0;
}
