#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

namespace details {

bool is_not_space(const char& c) noexcept {
  return c != ' ';
}

std::string trim_left(std::string s) {
  s.erase(s.cbegin(), std::find_if(s.cbegin(), s.cend(), is_not_space));
  return s;
}

std::string trim_right(std::string s) {
  s.erase(std::find_if(s.crbegin(), s.crend(), is_not_space).base(), s.cend());
  return s;
}

std::string trim(std::string s) {
  return trim_right(trim_left(std::move(s)));
}

double average_score(const std::vector<float>& scores) noexcept {
  return std::accumulate(scores.cbegin(), scores.cend(), 0.0f) /
      double(scores.size());
}

} // namespace details

void testFn() {
  std::cout << "1):  [" << details::trim_left(" This is a Message.") << "]"
            << std::endl;
  std::cout << "2):  [" << details::trim_right("This is a Message.  ") << "]"
            << std::endl;
  std::cout << "2):  [" << details::trim("    This is a Message.  ") << "]"
            << std::endl;
  std::cout << "4):  [" << details::average_score({1, 2, 3, 4, 5, 6, 7, 8, 9})
            << "]" << std::endl;
}

int main(int argc, char** argv) {
  testFn();
  return 0;
}
