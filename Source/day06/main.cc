#include "Core.hpp"
#include <cstdint>
#include <functional>
#include <iostream>
#include <ranges>
#include <set>
#include <utility>
#include <vector>

class Solution {
public:
  enum class Direction { Up, Right, Down, Left };
  struct Position {
    std::uint32_t x;
    std::uint32_t y;

    constexpr auto operator<=>(const Position&) const = default;
    // constexpr auto operator<(const Position& other) const -> bool {
    //   return x < other.x || (x == other.x && y < other.y);
    // }
  };

  Solution() = default;

  auto part1() const {
    using Dir = Direction;

    const auto rotate = [](Direction dir) -> Dir {
      switch (dir) {
      case Dir::Up:
        return Dir::Right;
      case Dir::Right:
        return Dir::Down;
      case Dir::Down:
        return Dir::Left;
      case Dir::Left:
        return Dir::Up;
      }
      std::unreachable();
    };

    auto p = find_guard_position();
    auto dir = Dir::Up;
    std::set<Position> seen{};

    seen.insert(p);

    const auto move = [&]() -> bool {
      switch (dir) {
      case Dir::Up:
        if (p.x == 0) {
          return false;
        }
        --p.x;
        break;
      case Dir::Right:
        if (p.y >= grid_.at(p.x).size()) {
          return false;
        }
        ++p.y;
        break;
      case Dir::Down:
        if (p.x >= grid_.size()) {
          return false;
        }
        ++p.x;
        break;
      case Dir::Left:
        if (p.y == 0) {
          return false;
        }
        --p.y;
        break;
      }

      seen.insert(p);
      if (obstacle_in_front(dir, p)) {
        dir = rotate(dir);
      }
      return true;
    };

    while (move()) {
      asm volatile("nop");
    }

    return seen.size();
  }

private:
  auto obstacle_in_front(Direction d, Position p) const -> bool {
    switch (d) {
    case Direction::Up:
      if (p.y == 0) {
        return false;
      }
      return grid_[p.x][p.y - 1] == '#';
    case Direction::Right:
      if (p.x >= grid_.size() - 1) {
        return false;
      }
      return grid_[p.x + 1][p.y] == '#';
    case Direction::Down:
      if (p.y >= grid_[p.x].size() - 1) {
        return false;
      }
      return grid_[p.x][p.y + 1] == '#';
    case Direction::Left:
      if (p.x == 0) {
        return false;
      }
      return grid_[p.x - 1][p.y] == '#';
    }
  }

  auto find_guard_position() const -> Position {
    for (auto i : std::ranges::iota_view{0UZ, grid_.size()}) {
      for (auto j : std::ranges::iota_view{0UZ, grid_[0].size()}) {
        if (grid_[i][j] == '^') {
          return {static_cast<std::uint32_t>(i), static_cast<std::uint32_t>(j)};
        }
      }
    };

    std::unreachable();
  }

  std::vector<std::vector<char>> grid_ = Aoc::file_to_2d_array("input.txt");
};

template <> struct std::hash<Solution::Position> {
  auto operator()(const Solution::Position& p) const -> size_t {
    char buff[sizeof(p) + 1];
    std::copy(reinterpret_cast<const char*>(&p),
              reinterpret_cast<const char*>(&p) + sizeof(p), buff);
    buff[sizeof(p)] = '\0';
    return std::hash<const char*>{}(buff);
  }
};

auto main() -> int {
  Solution s;
  std::cout << "Part 1: " << s.part1() << '\n';
}
