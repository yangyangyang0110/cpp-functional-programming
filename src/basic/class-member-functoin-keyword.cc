/* Proj: cpp-functional-programming
 * File: move-and-iterator.cc
 * Created Date: 2022/9/27
 * Author: YangYangYang (yangzilong@objecteye.com)
 * Description:
 * -----
 * Last Modified: 2022/9/27 00:07:50
 * Modified By: YangYangYang (yangzilong@objecteye.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>

#if 0
class NonCopyAble
{
public:
    NonCopyAble(const NonCopyAble &) = delete;
    NonCopyAble &operator=(const NonCopyAble &) = delete;

protected:
    NonCopyAble() = default;
    NonCopyAble(NonCopyAble &&) noexcept = default;
    NonCopyAble &operator=(NonCopyAble &&) noexcept = default;
};

struct Widget : public NonCopyAble {
    std::string name;

    Widget() { std::cout << "[Widget Constructor]" << std::endl; }
    ~Widget() { std::cout << "[Widget Destructor]" << std::endl; }

    Widget(Widget &&rhs) noexcept { std::cout << "[Rvalue Constructor]" << std::endl; }
    Widget &operator=(Widget &&rhs) noexcept
    {
        std::cout << "[Rvalue Assignment]" << std::endl;
        if (this == &rhs) return *this;
        return *this;
    }
};

void testFn()
{
    std::vector<Widget> inp(10);
    std::vector<Widget> output;
    std::cout << "Start Move Data" << std::endl;
    std::copy_if(std::make_move_iterator(std::begin(inp)),
                 std::make_move_iterator(std::end(inp)), std::back_inserter(output),
                 [](const Widget &) { return true; });

    std::vector<std::string> source = {"Move", "iterators", "in", "C++"};
    std::vector<std::string> destination;

    std::copy_if(std::make_move_iterator(std::begin(source)),
                 std::make_move_iterator(std::end(source)),
                 std::back_inserter(destination),
                 [](std::string const &word) { return word.length() == 4; });
    std::cout << "Source: ";
    for (auto const &w : source) std::cout << '"' << w << '"' << ' ';
    std::cout << "\nDestination: ";
    for (auto const &w : destination) std::cout << '"' << w << '"' << ' ';
}
#endif

struct Person {
  std::string first_name, second_name;

  // const: No NRVO when enable const.
  Person createWithFirstNameWithoutNRVO(std::string name) const {
    Person person = *this;
    person.first_name = std::move(name);
    return person;
  }

  Person createWithFirstName(std::string name) {
    Person person = *this;
    person.first_name = std::move(name);
    return person;
  }

  Person modifySecondName(std::string name) && {
    Person person = std::move(*this);
    person.second_name = std::move(name);
    return person;
  }

  friend std::ostream& operator<<(std::ostream& os, Person const& ins) {
    os << "[first_name: " << ins.first_name
       << " second_name: " << ins.second_name << "]";
    return os;
  }
};

void test2() {
  Person john{.first_name = "Yang", .second_name = "John"};
  std::cout << john << std::endl;
  Person tmp =
      john.createWithFirstNameWithoutNRVO("YYY").modifySecondName("ZZZ");
  std::cout << tmp << std::endl;
}

int main(int argc, char** argv) {
  test2();
  return 0;
}
