#include <fstream>
#include <iostream>
#include <istream>
#include <ranges>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class Solution {
public:
  Solution() {
    std::ifstream input("input.txt");
    propagate_members(input);
  }
  explicit Solution(std::istream& input) { propagate_members(input); }

  auto update_valid(const std::vector<int>& update) const {
    std::unordered_set<int> seen;
    for (const auto& n : update) {
      auto range = must_be_before_.equal_range(n);
      for (auto it = range.first; it != range.second; ++it) {
        if (seen.contains(it->second)) {
          return false;
        }
      }
      seen.emplace(n);
    }
    return true;
  }

  auto part1() const {
    unsigned total{};

    for (const auto& update : updates_) {
      if (update_valid(update)) {
        total += update.at(update.size() / 2);
      }
    }

    return total;
  }

  auto insert_update(std::vector<int>& update, int n) {}

  auto fix_update(const std::vector<int>& update) const {
    std::vector<int> result = update;

    for (auto i : std::ranges::iota_view{0UZ, result.size() - 1}) {
      for (auto j : std::ranges::iota_view{i + 1, result.size()}) {
        auto range = must_be_before_.equal_range(result[j]);
        for (auto it = range.first; it != range.second; ++it) {
          if (it->second == result[i]) {
            std::swap(result[j], result[i]);
            break;
          }
        }
      }
    }
    return result;
  }

  auto part2() const {
    unsigned total{};
    for (const auto& update : updates_) {
      if (!update_valid(update)) {
        auto ordered_update = fix_update(update);
        total += ordered_update.at(ordered_update.size() / 2);
      }
    }

    return total;
  }

  friend auto operator<<(std::ostream& os, const Solution& s) -> std::ostream& {
    os << "Rules:\n";
    for (const auto& [before, after] : s.must_be_before_) {
      os << before << " -> [" << after << "]\n";
    }
    os << "\nUpdates:\n";
    for (const auto& update : s.updates_) {
      os << "[";
      for (const auto& n : update) {
        os << n << ", ";
      }
      os << "]\n";
    }
    return os;
  }

private:
  void propagate_members(std::istream& input) {
    std::string line;
    while (std::getline(input, line)) {
      if (line.find('|') != std::string::npos) {
        std::istringstream iss(line);
        int before;
        int after;
        iss >> before;
        iss.ignore(1);
        iss >> after;

        must_be_before_.emplace(before, after);
      } else {
        std::istringstream iss(line);
        std::vector<int> update;
        int n;
        while (iss >> n) {
          update.emplace_back(n);
          if (char c = 0; (iss >> c), c != ',') {
            break;
          }
        }
        if (update.empty()) {
          continue;
        }
        updates_.emplace_back(std::move(update));
      }
    }
  }

  std::unordered_multimap<int, int>
      must_be_before_; // i.e. 3 -> [1, 2], 3 must be before 1, 2
  std::vector<std::vector<int>> updates_;
};

auto main() -> int {
  // std::istringstream iss{R"(47|53
  // 97|13
  // 97|61
  // 97|47
  // 75|29
  // 61|13
  // 75|53
  // 29|13
  // 97|29
  // 53|29
  // 61|53
  // 97|53
  // 61|29
  // 47|13
  // 75|47
  // 97|75
  // 47|61
  // 75|61
  // 47|29
  // 75|13
  // 53|13

  // 75,47,61,53,29
  // 97,61,53,29,13
  // 75,29,13
  // 75,97,47,61,53
  // 61,13,29
  // 97,13,75,29,47)"};
  // Solution s(iss);
  Solution s;

  std::cout << "Part 1: " << s.part1() << '\n';
  std::cout << "Part 2: " << s.part2() << '\n';
}
