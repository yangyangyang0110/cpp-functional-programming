/* Proj: cpp-functional-programming
 * File: simple-factory-02.cpp
 * Created Date: 2022/11/13
 * Author: YangYangYang (yangyangyang0110@outlook.com)
 * Description:
 * -----
 * Last Modified: 2022/11/13 11:33:27
 * Modified By: YangYangYang (yangyangyang0110@outlook.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <cassert>
#include <functional>
#include <iostream>
#include <map>
#include <memory>

// Define interface.
class Inference {
 public:
  virtual void Preprocess(bool b) noexcept = 0;
  virtual ~Inference() noexcept = default;

 private:
};

class Factory {
 public:
  // using Creator = std::function<std::shared_ptr<Inference>()>;
  using Creator = void*;
  using CreatorRegistry = std::map<const std::string, Creator>;

  template <typename T, typename... Args>
  static std::shared_ptr<Inference> create(
      const std::string_view name, Args&&... args) noexcept {
    using CreatorFunction = std::shared_ptr<T> (*)(Args...);
    auto creatorRegistry = getCreatorRegistry();
    auto it = creatorRegistry.find(std::string(name));
    return it != creatorRegistry.end()
        ? reinterpret_cast<CreatorFunction>(it->second)(
              std::forward<Args>(args)...)
        : nullptr;
  }

  static void addCreator(const std::string& name, Creator creator) noexcept {
    getCreatorRegistry()[name] = creator;
  }

 private:
  static CreatorRegistry& getCreatorRegistry() noexcept {
    static CreatorRegistry creatorRegistry;
    return creatorRegistry;
  }
};

template <
    typename T,
    typename... Args,
    std::enable_if_t<std::is_constructible_v<T, Args...>>* = nullptr>
std::shared_ptr<T> __create(Args&&... args) noexcept(
    std::is_nothrow_constructible_v<T, Args...>) {
  return std::make_shared<T>(std::forward<Args>(args)...);
}

#define REGISTER_CLASS(type, ...) \
  Factory::addCreator(            \
      #type, (Factory::Creator)(&std::make_shared<type, __VA_ARGS__>));

constexpr inline const char* bool2str(bool b) noexcept {
  return b ? "true" : "false";
}

class Detect : public Inference {
 public:
  explicit Detect(std::string data) : data_(std::move(data)) {}

  void Preprocess(bool b) noexcept final {
    std::cout << "Detect: " << bool2str(b) << " " << data_ << std::endl;
  }
  ~Detect() noexcept override = default;

 private:
  std::string data_;
};

class Classify : public Inference {
 public:
  explicit Classify(long id) {}
  void Preprocess(bool b) noexcept final {
    std::cout << "Classify: " << bool2str(b) << std::endl;
  }
};

/**
 * @brief
 */
void test() {
  REGISTER_CLASS(Detect, std::string)
  REGISTER_CLASS(Classify, long)
  auto ptr = Factory::create<Detect>("Detect", std::string("Hello world"));
  assert(ptr != nullptr);
  ptr->Preprocess(true);
  // INTERRUPTED, char and string type convert.
  auto ptr2 = Factory::create<Detect>("Detect", "2222");
  assert(ptr2 != nullptr);
  std::cout << ptr.get() << "  " << ptr2.get() << std::endl;
}

int main() {
  test();
  return 0;
}
