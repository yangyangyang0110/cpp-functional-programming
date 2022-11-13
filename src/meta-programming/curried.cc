/* Proj: cpp-functional-programming
 * File: curried.cc
 * Created Date: 2022/10/8
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/8 06:01:36
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <functional>
#include <iostream>
#include <type_traits>

template <typename Arg>
void echo(Arg&& arg) {
  std::cout << std::forward<Arg>(arg) << std::endl;
}

template <typename F, typename... Args>
void invokeResult(F f, Args&&... args) {
  f(std::forward<Args>(args)...);
}

template <typename F, typename... Args>
void invokeFunctor(F f, Args&&... args) {
  std::invoke(f, std::forward<Args>(args)...);
}

template <typename F, typename... Args>
void invokeTupleFunctor(F f, Args&&... args) {
  auto all_args =
      std::tuple<std::decay_t<Args>...>(std::forward<Args>(args)...);
  std::apply(f, std::move(all_args));
}

template <typename T>
struct Foo {
  explicit Foo(T&& v) : v_(std::forward<T>(v)) {}

  void echo() const { std::cout << v_ << std::endl; };

private:
  T v_;
};

// 判断是否可以调用
template <typename F, typename... CapturedArgs>
class Curried {
public:
  // using CaptureArgsTuple = std::tuple<std::decay_t<CapturedArgs>...>;

  template <typename... Args>
  static auto capture_by_copy(Args&&... args) {
    return std::make_tuple<Args...>(std::forward<Args>(args)...);
  }

  Curried(F f, CapturedArgs... args)
      : function_(f), args_tuple_(capture_by_copy(std::move(args)...)) {}

  Curried(F f, std::tuple<CapturedArgs...> args_tuple)
      : function_(f), args_tuple_(std::move(args_tuple)) {}

  template <typename... Args>
  auto operator()(Args... args) {
    // concat args.
    auto args_tuple = capture_by_copy(std::forward<Args>(args)...);
    auto all_args_tuple = std::tuple_cat(args_tuple_, std::move(args_tuple));

    if constexpr (std::is_invocable_v<F, CapturedArgs..., Args...>) {
      return std::apply(function_, all_args_tuple);
    } else {
      return Curried<F, CapturedArgs..., Args...>(function_, all_args_tuple);
    }
  }

private:
  F function_;
  std::tuple<CapturedArgs...> args_tuple_;
};

void test() {
  invokeResult([]() { std::cout << "Lambda Function called " << std::endl; });
  invokeResult(
      [](int x, int y) { std::cout << x << " " << y << std::endl; }, 1, 2);
  std::apply(
      [](int x, int y) { std::cout << x << " " << y << std::endl; },
      std::tuple(1, 2));

  invokeResult(echo<std::string>, "echo called.");
  Foo<std::string> f("foo::f called.");
  invokeFunctor(&Foo<std::string>::echo, &f);
}

void test_curried() {
  // 值传递.
  Curried curried(
      [](int x, int y, int z) {
        std::cout << x << " + " << y << " + " << z << " = " << (x + y + z)
                  << std::endl;
      },
      1);

  auto plus_1_3 = curried(3);
  plus_1_3(5);

  // 对于比较重的资源可以使用值的引用.
  Curried c2(
      []<typename T>(std::ostream& os, const std::string& t0, T t1, auto t2) {
        os << t0 << " " << t1 << " " << t2;
      });
  // 引用 + 常引用 + 值传递.
  std::string message = "action";
  c2(std::ref(std::cout), std::cref(message), "hello", "world2");

  // TODO: 不能判断何时执行,
  // 这个问题在添加模版参数后比较明显(模版参数实例化后的类型). guess -> T: const
  // std::string &
  Curried c3([]<typename T>(std::ostream& os, const T& t0, T t1, auto t2) {
    os << t0 << " " << t1 << " " << t2;
  });

  c3(std::ref(std::cout), std::cref(message), "hello", "world3");
}

int main() {
  // test();
  test_curried();
  return 0;
}