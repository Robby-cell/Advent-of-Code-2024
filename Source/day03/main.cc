#include "Core.hpp"

#include <fstream>
#include <iostream>
#include <string>

#include <regex>

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

auto main() -> int { std::cout << "Part 1: " << part1() << '\n'; }
