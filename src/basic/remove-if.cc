/* Proj: cpp-functional-programming
 * File: remove-if.cc
 * Created Date: 2022/10/3
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/3 11:48:08
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

struct MoveOnly {
public:
  MoveOnly(MoveOnly const&) = delete;
  MoveOnly& operator=(MoveOnly const&) = delete;

protected:
  MoveOnly() = default;
  MoveOnly(MoveOnly&&) = default;
  MoveOnly& operator=(MoveOnly&&) = default;
};

template <typename T>
struct Image : public MoveOnly {
  T* data;

  explicit Image() : data(new T) {}

  ~Image() noexcept {
    std::cout << "Image<T> Destructor" << std::endl;
    if (data != nullptr) {
      delete data;
      data = nullptr;
    }
  }
};

template <typename T>
struct Image<T[]> : public MoveOnly {
  T* data;
  size_t size;

  explicit Image(size_t size) : data(new T[size]), size(size) {}

  Image(Image&& rhs) noexcept : data(rhs.data), size(rhs.size) {
    rhs.data = nullptr;
    rhs.size = 0UL;
  }

  Image& operator=(Image&& rhs) noexcept {
    if (this == &rhs) {
      return *this;
    }

    if (data != nullptr) {
      delete[] data;
      data = nullptr;
    }

    data = rhs.data;
    size = rhs.size;
    rhs.data = nullptr;
    rhs.size = 0UL;
    return *this;
  }

  ~Image() noexcept {
    std::cout << "Image<T[]> Destructor" << std::endl;
    if (data != nullptr) {
      delete[] data;
      data = nullptr;
    }
    size = 0UL;
  }

  friend std::ostream& operator<<(std::ostream& os, Image<T[]> const& ins) {
    os << "[";
    for (size_t i = 0; i < ins.size; ++i) {
      os << ins.data[i] << " ";
    }
    os << "], size: " << ins.size;
    return os;
  }
};

struct Response {
  bool is_error;
  std::string data;
  friend std::ostream& operator<<(std::ostream& os, Response const& ins) {
    return os << "data: " << ins.data;
  }
};

void testBasic() {
  auto print = []<typename T>(std::vector<T> const& vec) {
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
              << std::endl;
    for (const auto& item : vec) {
      std::cout << item << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
              << std::endl;
  };
  std::vector<Response> responses = {
      {.is_error = true, .data = "200"},
      {.is_error = false, .data = "400"},
      {.is_error = true, .data = "222"},
      {.is_error = false, .data = "500"}};
  print(responses);

  auto it =
      std::remove_if(responses.begin(), responses.end(), [](const auto& item) {
        return item.is_error;
      });
  print(responses);

  responses.erase(it, responses.end());

  print(responses);
}

void testRAII() {
  /**
   * @brief 会析构Element
   */
  auto print = []<typename T>(std::vector<T> const& vec) {
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
              << std::endl;
    for (const auto& item : vec) {
      std::cout << item << std::endl;
    }
    std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
              << std::endl;
  };

  std::vector<Image<char[]>> images;
  images.reserve(10);
  for (const std::weakly_incrementable auto& i : std::views::iota(1, 10)) {
    images.emplace_back(i);
  }

  print(images);

  std::cout << "Before Erasing" << std::endl;
  images.erase(
      std::remove_if(
          images.begin(),
          images.end(),
          [](const auto& image) -> bool { return image.size % 2; }),
      images.end());
  std::cout << "After Erasing" << std::endl;
  print(images);
}

int main() {
  // testBasic();
  testRAII();
  return 0;
}