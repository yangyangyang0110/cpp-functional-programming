/* Proj: cpp-functional-programming
 * File: simple-factory.cpp
 * Created Date: 2022/11/13
 * Author: YangYangYang (yangyangyang0110@outlook.com)
 * Description:
 * -----
 * Last Modified: 2022/11/13 11:17:43
 * Modified By: YangYangYang (yangyangyang0110@outlook.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <iostream>
#include <memory>
// Define interface.
class Inference {
 public:
  virtual void Preprocess(bool b) noexcept = 0;
  virtual ~Inference() noexcept = default;

 private:
};

namespace details {

constexpr inline const char* bool2str(bool b) noexcept {
  return b ? "true" : "false";
}

class Detect : public Inference {
 public:
  void Preprocess(bool b) noexcept final {
    std::cout << "Detect: " << bool2str(b) << std::endl;
  }
};

class Classify : public Inference {
 public:
  void Preprocess(bool b) noexcept final {
    std::cout << "Classify: " << bool2str(b) << std::endl;
  }
};
} // namespace details

enum class InferenceType { DETECT, CLASSIFY };

std::unique_ptr<Inference> make_inference(InferenceType type) noexcept {
  switch (type) {
    case InferenceType::DETECT:
      return std::make_unique<details::Detect>();
    case InferenceType::CLASSIFY:
      return std ::make_unique<details::Classify>();
    default:
      std::cerr << "Unknown Inference" << std::endl;
      return nullptr;
  }
}

/**
 * @brief
 */
void test() {
  make_inference(InferenceType::DETECT)->Preprocess(true);
  make_inference(InferenceType::CLASSIFY)->Preprocess(false);
}

int main() {
  test();
  return 0;
}