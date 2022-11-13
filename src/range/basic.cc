/* Proj: cpp-functional-programming
 * File: basic.cc
 * Created Date: 2022/10/5
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/5 12:03:54
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <iostream>
#include <ranges>
#include <string>

std::string to_lower(const std::string& s) {
  s | std::views::transform([](const char c) { return std::tolower(c); });
  return "";
}

void test() {
  std::string s = " This is a String Var.";
  auto res = to_lower(s);
  std::cout << res << std::endl;
}

int main() {
  test();
  return 0;
}