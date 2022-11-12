/* Proj: cpp-functional-programming
 * File: for-future.cpp
 * Created Date: 2022/11/12
 * Author: YangYangYang (yangyangyang0110@outlook.com)
 * Description:
 * -----
 * Last Modified: 2022/11/12 19:18:30
 * Modified By: YangYangYang (yangyangyang0110@outlook.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

// #include <experimental/socket>
// using namespace std::experimental::net;

#include <future>

void test() { std::future<void> f; }

int main()
{
    test();
    return 0;
}
