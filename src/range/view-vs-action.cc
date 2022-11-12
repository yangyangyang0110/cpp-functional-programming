/* Proj: cpp-functional-programming
 * File: view-vs-action.cc
 * Created Date: 2022/10/4
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/4 09:02:14
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <iostream>
#include <istream>
#include <ranges>
#include <vector>

void test()
{
    std::vector<std::string> names = {"1", "22", "333"};
    for (const auto &name :
         names | std::views::filter([](const std::string &s) { return s.size() > 1; }) |
             std::views::transform([](const std::string &s) { return s + "-"; }) |
             std::views::take(1)) {
        std::cout << name << std::endl;
    }
}

void test_word_count_by_range()
{
    /**
     * @brief 统计词频 using range.
     */

    // std::vector<std::string> data = std::istream_range<std::string>(std::cin);
}

int main(int argc, char **argv)
{
    // test();
    test_word_count_by_range();
    return 0;
}
