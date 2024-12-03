#ifndef CSC_CORE_HPP
#define CSC_CORE_HPP

#include <istream>
#include <string>
#include <string_view>
namespace Aoc {
auto read_file(std::string_view path) -> std::string;
auto read_file(std::istream& file) -> std::string;

constexpr auto Difference(auto a, auto b) { return a > b ? a - b : b - a; }
} // namespace Aoc

#endif // CSC_CORE_HPP
