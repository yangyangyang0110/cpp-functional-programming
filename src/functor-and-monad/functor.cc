/* Proj: cpp-functional-programming
 * File: functor.cc
 * Created Date: 2022/10/9
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/9 13:09:46
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <iostream>
#include <ranges>

auto transform(auto&& value) {
  return std::forward<decltype(value)>(value);
}

void test() {
  std::string message = "Hello world!";
  const auto* ptr = &message;
  auto&& u1 = transform(message);
  const auto* ptr2 = &u1;
  u1 += "1111";
  std::cout << ptr << " " << message << std::endl;
  std::cout << ptr2 << " " << u1 << std::endl;
}

int main() {
  printf("%p\n", main);
  test();
  return 0;
}
