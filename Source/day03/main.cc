#include "Core.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include <regex>
#include <string_view>

auto find_all_matches(const std::string& buf) {
  unsigned total = 0;

  std::smatch res;
  std::regex mul_regex(R"(mul\((\d+),(\d+)\))");

  auto search_begin(buf.cbegin());
  while (regex_search(search_begin, buf.cend(), res, mul_regex)) {
    auto match = res[0].str();
    auto comma = match.find(',');
    auto n1 = std::stoi(match.substr(4, comma - 4));
    auto n2 = std::stoi(match.substr(comma + 1, match.size() - comma - 2));
    total += n1 * n2;
    search_begin = res.suffix().first;
  }

  return total;
}

auto do_part1(std::istream& input) -> unsigned {
  auto buf = Aoc::read_file(input);
  return find_all_matches(buf);
}

auto part1() {
  std::ifstream input("input.txt");
  // std::istringstream input{
  //     R"(xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5)))"};

  return do_part1(input);
}

auto do_part2(std::istream& input) -> unsigned {
  auto buf = Aoc::read_file(input);

  unsigned total = 0;

  while (!buf.empty()) {
    auto next_dont = Aoc::find_substr(buf, "don't()");
    // either we have npos, pass npos to the count so we dont overflow.
    // or the location the next don't() was count + length of don't()
    auto search_area = buf.substr(
        0, (next_dont == std::string_view::npos) ? next_dont : next_dont + 7);
    total += find_all_matches(search_area);
    if (next_dont == std::string_view::npos) {
      break;
    }

    // this is the same thing... BUT this is offset by search_area.length()
    auto next_do = Aoc::find_substr(buf.substr(search_area.length()), "do()");
    if (next_do == std::string_view::npos) {
      break;
    }
    // so we need to add the offset back on again
    // if we dont do this, it double dips on some mul instructions
    buf = buf.substr(next_do + 4 + search_area.length());
  }

  return total;
}

auto part2() {
  std::ifstream input("input.txt");
  // std::istringstream input("xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64]("
  //                          "mul(11,8)undo()?mul(8,5))");
  return do_part2(input);
}

auto main() -> int {
  std::cout << "Part 1: " << part1() << '\n';
  std::cout << "Part 2: " << part2() << '\n';
  return 0;
}
