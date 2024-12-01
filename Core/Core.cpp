#include "Core.hpp"

#include <fstream>
#include <iostream>

namespace Aoc {
auto read_file(std::string_view path) -> std::string {
  std::ifstream file(path.data());
  if (!file.is_open()) {
    std::cerr << "Could not open file: " << path << std::endl;
    return {};
  }
  return std::string(std::istreambuf_iterator<char>(file), {});
}
} // namespace Aoc
