/* Proj: cpp-functional-programming
 * File: mock-view-on-operator-increment.cc
 * Created Date: 2022/10/3
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/10/3 21:26:41
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

enum class Gender : int8_t {
  FEMALE = 0,
  MALE = 1,
};

struct Person {
  std::string name;
  Gender gender;

  friend std::ostream& operator<<(std::ostream& os, const Person& ins) {
    return os << "Person: [name=" << ins.name
              << " gender=" << static_cast<int32_t>(ins.gender) << "]";
  }
};

template <typename Prediction, typename T = Person>
class Filter {
private:
  std::vector<T> arr_;
  decltype(arr_.begin()) current_position_;
  Prediction prediction_;

public:
  Filter(std::initializer_list<T> list, Prediction&& prediction)
      : arr_(std::move(list)),
        current_position_(arr_.begin() - 1),
        prediction_(std::forward<Prediction>(prediction)) {
    ++(*this);
  }

  auto& pos() { return current_position_; }

  [[nodiscard]] bool is_eof() const { return current_position_ >= arr_.end(); }

  auto& operator++() {
    assert(current_position_ < arr_.size());
    current_position_ =
        std::find_if(current_position_ + 1, arr_.end(), prediction_);
    return *this;
  }
};

void test_filter() {
  Filter persons(
      {
          {.name = "f0", .gender = Gender::FEMALE},
          {.name = "m0", .gender = Gender::MALE},
          {.name = "f1", .gender = Gender::FEMALE},
          {.name = "m1", .gender = Gender::MALE},
          {.name = "f2", .gender = Gender::FEMALE},
          {.name = "m2", .gender = Gender::MALE},
      },
      []<typename T>(const T& item) { return item.gender == Gender::FEMALE; });

  for (const auto& it = persons.pos(); !persons.is_eof(); ++persons) {
    std::cout << *it << std::endl;
  }

  // or

  // while (!persons.is_eof()) {
  //     std::cout << *persons.pos() << std::endl;
  //     ++persons;
  // }
}

template <typename UnaryOperator, typename T = Person>
class Transform {
private:
  std::vector<T> arr_;
  decltype(arr_.begin()) current_position_;
  UnaryOperator unary_operator_;

public:
  Transform(std::initializer_list<T> list, UnaryOperator&& unary_operator)
      : arr_(std::move(list)),
        current_position_(arr_.begin()),
        unary_operator_(std::forward<UnaryOperator>(unary_operator)) {}

  auto& pos() { return current_position_; }

  [[nodiscard]] bool is_eof() const { return current_position_ >= arr_.end(); }

  auto& operator++() {
    assert(current_position_ < arr_.size());
    ++current_position_;
    return *this;
  }

  T operator*() const { return unary_operator_(*current_position_); }
};

void test_transform() {
  Transform persons(
      {
          {.name = "f0", .gender = Gender::FEMALE},
          {.name = "m0", .gender = Gender::MALE},
          {.name = "f1", .gender = Gender::FEMALE},
          {.name = "m1", .gender = Gender::MALE},
          {.name = "f2", .gender = Gender::FEMALE},
          {.name = "m2", .gender = Gender::MALE},
      },
      [](const Person& item) {
        Person person = item;
        std::transform(
            item.name.cbegin(),
            item.name.cend(),
            person.name.begin(),
            [](const char& c) { return toupper(c); });
        return person;
      });

  for (const auto& it = persons.pos(); !persons.is_eof(); ++persons) {
    std::cout << *persons << std::endl;
  }
}

int main() {
  // test_filter();
  test_transform();
  return 0;
}