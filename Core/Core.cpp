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
  return read_file(file);
}
auto read_file(std::istream& file) -> std::string {
  return std::string(std::istreambuf_iterator<char>(file), {});
}

auto file_to_2d_array(std::string_view filename)
    -> std::vector<std::vector<char>> {
  std::vector<std::vector<char>> data;
  std::ifstream input(filename.data());
  std::string line;

  while (std::getline(input, line)) {
    data.emplace_back(line.begin(), line.end());
  }

  return data;
}
} // namespace Aoc
