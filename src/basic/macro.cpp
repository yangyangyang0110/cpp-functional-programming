/* Proj: cpp-functional-programming
 * File: macro.cpp
 * Created Date: 2022/11/13
 * Author: YangYangYang (yangyangyang0110@outlook.com)
 * Description:
 * -----
 * Last Modified: 2022/11/13 13:42:52
 * Modified By: YangYangYang (yangyangyang0110@outlook.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <iostream>
#include <string_view>

class Manager {
 public:
  static void print(const std::string_view data) noexcept {
    std::cout << data << std::endl;
  }
};

#define CALL_FUNCTION(x, ...) Manager::print(#x);

void test() {
  CALL_FUNCTION(Hello);
}

int main() {
  test();
  return 0;
}
