/* Proj: cpp-functional-programming
 * File: generic-functional.cpp
 * Created Date: 2022/11/13
 * Author: YangYangYang (yangyangyang0110@outlook.com)
 * Description:
 * -----
 * Last Modified: 2022/11/13 23:35:27
 * Modified By: YangYangYang (yangyangyang0110@outlook.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <functional>
#include <memory>
#include <string>

class A {
public:
  explicit A(std::string name) noexcept : name_(std::move(name)){};

private:
  std::string name_;
};

class B {
public:
  explicit B(int v) noexcept : val_(v){};

private:
  int val_;
};

/**
 * @brief 如何声明能表示A和B的构造指针?
 */

// 方法1: void* + reinterpret
void method1() {
  using PtrType = void*;
  auto ca = reinterpret_cast<PtrType>(&std::make_shared<A, std::string>);
}

void test() {}

int main() {
  test();
  return 0;
}
