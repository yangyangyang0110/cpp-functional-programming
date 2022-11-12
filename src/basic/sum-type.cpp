/* Proj: cpp-functional-programming
 * File: sum-type.cpp
 * Created Date: 2022/11/5
 * Author: YangYangYang (yangyangyang0110@outlook.com)
 * Description:
 * -----
 * Last Modified: 2022/11/5 13:43:40
 * Modified By: YangYangYang (yangyangyang0110@outlook.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <cstddef>
#include <iostream>
#include <variant>

template <class T> struct Left {
    T val;
};

template <class T> struct Right {
    T val;
};

template <class T, class U> using Either = std::variant<Left<T>, Right<U>>;

Either<int, int> TrySomething()
{
    // get off my case about rand(), I know it's bad
    const auto random_value = rand();
    if (random_value % 2 == 0) return Left<int>{0};
    else return Right<int>{0};
}

struct visitor {
    template <class T> void operator()(const Left<T> &val_wrapper)
    {
        std::cout << "Success! Value is: " << val_wrapper.val << std::endl;
    }

    template <class T> void operator()(const Right<T> &val_wrapper)
    {
        std::cout << "Failure! Value is: " << val_wrapper.val << std::endl;
    }
};

int main()
{
    visitor v;
    for (size_t i = 0; i < 10; ++i) {
        auto res = TrySomething();
        std::visit(v, res);
    }
}
