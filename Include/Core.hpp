#ifndef CSC_CORE_HPP
#define CSC_CORE_HPP

#include <istream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>
namespace Aoc {
auto read_file(std::string_view path) -> std::string;
auto read_file(std::istream& file) -> std::string;

constexpr auto Difference(auto a, auto b) { return a > b ? a - b : b - a; }

constexpr auto find_substr(std::string_view haystack, std::string_view needle)
    -> std::string_view::size_type {
  for (auto i : std::ranges::iota_view{0UZ, haystack.size()}) {
    if (haystack.substr(i, needle.size()) == needle) {
      return i;
    }
  }
  return std::string_view::npos;
}

auto file_to_2d_array(std::string_view filename)
    -> std::vector<std::vector<char>>;
} // namespace Aoc

#endif // CSC_CORE_HPP
