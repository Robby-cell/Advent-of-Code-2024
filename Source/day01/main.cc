#include "Core.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <numeric>
#include <ranges>
#include <unordered_map>
#include <vector>

struct Input {
  std::vector<unsigned> list1;
  std::vector<unsigned> list2;
};

auto get_input() {
  std::ifstream input_file("input.txt");
  Input input;
  while (input_file.good()) {
    unsigned n1;
    unsigned n2;
    input_file >> n1 >> n2;
    input.list1.push_back(n1);
    input.list2.push_back(n2);
  }

  std::sort(input.list1.begin(), input.list1.end());
  std::sort(input.list2.begin(), input.list2.end());

  return input;
}

auto part1() {
  auto input = get_input();

  auto zip = std::ranges::views::zip(input.list1, input.list2);
  auto sum =
      std::accumulate(zip.begin(), zip.end(), 0U, [](auto sum, auto pair) {
        return sum + Aoc::Difference(std::get<0>(pair), std::get<1>(pair));
      });

  return sum;
}

auto part2() {
  auto input = get_input();
  // Input input{{1, 2, 3, 3, 3, 4}, {3, 3, 3, 4, 5, 9}};

  std::unordered_map<unsigned, unsigned> map;
  for (auto number : input.list2) {
    ++map[number];
  }

  unsigned sum{};

  for (auto number : input.list1) {
    if (map.contains(number)) {
      sum += number * map[number];
    }
  }

  return sum;
}

auto main() -> int {
  auto p2 = part2();
  std::cout << p2 << '\n';
}
