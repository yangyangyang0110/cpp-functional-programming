/* Proj: cpp-functional-programming
 * File: cache-value-at-fibonacci.cc
 * Created Date: 2022/10/3
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/3 13:31:04
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <chrono>
#include <iostream>
#include <map>

class Timer {
 private:
  std::chrono::system_clock::time_point now_;

 public:
  explicit Timer(bool is_reset = false) {
    if (is_reset)
      Reset();
  }

  void Reset() { now_ = std::chrono::system_clock::now(); }

  template <typename TimeType = std::chrono::milliseconds>
  long long int Cost() {
    return std::chrono::duration_cast<TimeType>(
               std::chrono::system_clock::now() - now_)
        .count();
  }
};

unsigned int fib(unsigned int n) {
  return n == 0 || n == 1 ? n : fib(n - 1) + fib(n - 2);
}

void fib_test() {
  Timer timer;
  timer.Reset();
  // 3996334433, 18139ms.
  std::cout << fib(50) << std::endl;
  std::cout << "Time Cost: " << timer.Cost() << " ms." << std::endl;
}

template <typename T = unsigned int>
class FibCache {
 private:
  T last_;
  T previous_;
  size_t size_;

 public:
  FibCache() : previous_{0}, last_{1}, size_{2} {}

  [[nodiscard]] const size_t& size() const { return size_; }

  T operator[](unsigned int n) const {
    return n == size_ - 1 ? last_
        : n == size_ - 2  ? previous_
                          : throw std::out_of_range("out of range.");
  }

  void push(T v) {
    size_++;
    previous_ = last_;
    last_ = v;
  }
};

unsigned int fib_cache(unsigned int n) {
  static FibCache g_fib_cache;
  if (g_fib_cache.size() > n) {
    return g_fib_cache[n];
  } else {
    const auto result = fib_cache(n - 1) + fib_cache(n - 2);
    g_fib_cache.push(result);
    return result;
  }
}

void fib_cache_test() {
  Timer timer;
  timer.Reset();
  // 3996334433 1ms.
  std::cout << fib_cache(50) << std::endl;
  std::cout << "Time Cost: " << timer.Cost() << " ms." << std::endl;
}

// Generalized memory
template <typename Result, typename... Args>
auto make_memoized(Result (*f)(Args...)) {
  std::map<std::tuple<Args...>, Result> cache;
  return [f, cache](Args... args) mutable -> Result {
    const auto args_tuple = std::make_tuple(args...);
    const auto it = cache.find(args_tuple);
    if (it == cache.end()) {
      auto result = f(args...);
      cache[args_tuple] = result;
      return result;
    } else {
      return it->second;
    }
  };
}

void fib_memoized() {
  auto fib_mem = make_memoized(fib_cache);
  Timer timer;
  timer.Reset();
  fib_mem(50);
  std::cout << "Time Cost: " << timer.Cost() << " ms." << std::endl;
  fib_mem(50);
  std::cout << "Time Cost: " << timer.Cost() << " ms." << std::endl;
}

int main() {
  // fib_test();
  // fib_cache_test();
  fib_memoized();
  return 0;
}