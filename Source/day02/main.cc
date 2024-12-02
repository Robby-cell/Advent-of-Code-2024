#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Report {
  std::vector<int> levels;

  auto push_back(int level) -> decltype(auto) {
    levels.push_back(level);
    return *this;
  }

  auto is_safe_after_remove() {
    if (is_safe()) {
      return true;
    }

    for (std::size_t i = 0; i < levels.size(); ++i) {
      auto clone = *this;
      clone.levels.erase(clone.levels.begin() + i);
      if (clone.is_safe()) {
        levels.erase(levels.begin() + i);
        return true;
      }
    }
    return false;
  }

  auto is_safe() const -> bool {
    auto ascending_or_descending =
        std::is_sorted(levels.begin(), levels.end()) ||
        std::is_sorted(levels.rbegin(), levels.rend());
    if (!ascending_or_descending) {
      return false;
    }

    for (std::size_t i = 0; i < levels.size() - 1; ++i) {
      if (auto diff = std::abs(levels.at(i) - levels.at(i + 1));
          !diff || diff > 3) {
        return false;
      }
    }
    return true;
  }
};

auto do_part1(std::istream& in) -> std::uint32_t {
  std::uint32_t count = 0;
  for (std::string line; std::getline(in, line);) {
    Report report;
    std::istringstream iss(line);

    for (int level; iss >> level;) {
      report.push_back(level);
    }

    if (report.is_safe()) {
      ++count;
    }
  }

  return count;
}

auto part1() {
  std::ifstream in("input.txt");
  return do_part1(in);
}

auto do_part2(std::istream& in) -> std::uint32_t {
  std::uint32_t count = 0;
  for (std::string line; std::getline(in, line);) {
    Report report;
    std::istringstream iss(line);

    for (int level; iss >> level;) {
      report.push_back(level);
    }

    if (report.is_safe_after_remove()) {
      ++count;
    }
  }
  return count;
}

auto part2() {
  std::ifstream in("input.txt");
  return do_part2(in);
}

auto main() -> int {
  std::cout << "Part 1: " << part1() << '\n';
  std::cout << "Part 2: " << part2() << '\n';
}
