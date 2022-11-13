/* Proj: cpp-functional-programming
 * File: config-design.cpp
 * Created Date: 2022/11/4
 * Author: YangYangYang (yangyangyang0110@outlook.com)
 * Description:
 * -----
 * Last Modified: 2022/11/4 23:19:10
 * Modified By: YangYangYang (yangyangyang0110@outlook.com)
 * -----
 * Copyright (c) 2022  . All rights reserved.
 */
#include <array>
#include <map>
#include <optional>
#include <string>
#include <variant>

struct DatetimeParam {
  std::array<std::string, 7> daytime;
};

struct FaceParam {};

struct PedestrianParam {};

using TaskId = std::string;

enum class AlgorithmType {};

struct TaskAndAlgorithm {
  TaskId taskId;
  AlgorithmType algorithmType;

  bool operator<(const TaskAndAlgorithm& other) const noexcept {
    return std::tie(taskId, algorithmType) <
        std::tie(other.taskId, other.algorithmType);
  }
};

class Config {
public:
  using Key = TaskAndAlgorithm;
  using Value = std::variant<FaceParam, PedestrianParam>;

  static void addParam(const Key& key, Value&& value) noexcept {
    map_[key] = value;
  }

  static std::optional<Value> getParam(const Key& key) noexcept {
    auto it = map_.find(key);
    return it != map_.end() ? std::make_optional(it->second) : std::nullopt;
  }

private:
  inline static std::map<Key, Value> map_;
};

void test() {}

int main() {
  test();
  return 0;
}
