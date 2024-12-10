#include "Core.hpp"
#include <cstddef>
#include <functional>
#include <iostream>
#include <ostream>
#include <ranges>
#include <unordered_set>
#include <vector>

using std::ranges::iota_view;

struct Position {
    int row;
    int col;
    friend auto operator<=>(const Position& self,
                            const Position& that) = default;

    friend auto operator<<(std::ostream& os, const Position& p)
        -> decltype(auto) {
        return os << '(' << p.row << ", " << p.col << ')';
    }
};

struct Path {
    Position origin;
    Position dest;

    friend auto operator<=>(const Path& self, const Path& that) = default;
};

template <> struct std::hash<Position> {
    auto operator()(const Position& position) const {
        return std::hash<int>{}(position.row) ^ std::hash<int>{}(position.col);
    }
};
template <> struct std::hash<Path> {
    auto operator()(const Path& path) const {
        return std::hash<Position>{}(path.origin) ^
               std::hash<Position>{}(path.dest);
    }
};

struct Solution {
    Solution() = default;

    auto paths_from_expect(std::unordered_set<Path>& set, Position origin,
                           std::ptrdiff_t row, std::ptrdiff_t col,
                           char expected) const {

        if (row < 0 || row >= grid.size() || col < 0 ||
            col >= grid[row].size()) {
            return;
        }

        if (grid[row][col] != expected) {
            return;
        }

        if (expected == '9') {
            Path path{origin, Position(row, col)};
            if (!set.contains(path)) {
                set.emplace(path);
            }
            return;
        }

        paths_from_expect(set, origin, row - 1, col, expected + 1);
        paths_from_expect(set, origin, row, col + 1, expected + 1);
        paths_from_expect(set, origin, row + 1, col, expected + 1);
        paths_from_expect(set, origin, row, col - 1, expected + 1);
    }

    auto paths_from(std::unordered_set<Path>& set, std::ptrdiff_t row,
                    std::ptrdiff_t col) const {
        if (grid[row][col] != '0') {
            return;
        }

        paths_from_expect(set, Position(row, col), row, col, '0');
    }

    auto part1() const {
        std::unordered_set<Path> set;

        for (auto row : iota_view{0UZ, grid.size()}) {
            for (auto col : iota_view{0UZ, grid[row].size()}) {
                paths_from(set, row, col);
            }
        }

        // for (const auto& p : set) {
        //     std::cout << p.origin << " -> " << p.dest << '\n';
        // }

        return set.size();
    }

    [[nodiscard]] auto paths_from_expect_part2(std::ptrdiff_t row,
                                               std::ptrdiff_t col,
                                               char expected) const {

        if (row < 0 || row >= grid.size() || col < 0 ||
            col >= grid[row].size()) {
            return 0;
        }

        if (grid[row][col] != expected) {
            return 0;
        }

        if (expected == '9') {
            return 1;
        }

        return paths_from_expect_part2(row - 1, col, expected + 1) +
               paths_from_expect_part2(row, col + 1, expected + 1) +
               paths_from_expect_part2(row + 1, col, expected + 1) +
               paths_from_expect_part2(row, col - 1, expected + 1);
    }

    [[nodiscard]] auto paths_from_part2(std::ptrdiff_t row,
                                        std::ptrdiff_t col) const {
        if (grid[row][col] != '0') {
            return 0;
        }
        return paths_from_expect_part2(row, col, '0');
    }

    auto part2() const {
        auto total = 0;
        for (auto row : iota_view{0UZ, grid.size()}) {
            for (auto col : iota_view{0UZ, grid[row].size()}) {
                total += paths_from_part2(row, col);
            }
        }

        // for (const auto& p : set) {
        //     std::cout << p.origin << " -> " << p.dest << '\n';
        // }

        return total;
    }

    std::vector<std::vector<char>> grid = Aoc::file_to_2d_array("input.txt");
};

auto main() -> int {
    Solution s;
    std::cout << "Part 1: " << s.part1() << '\n';
    std::cout << "Part 2: " << s.part2() << '\n';
}
