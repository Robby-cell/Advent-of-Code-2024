#include "Core.hpp"
#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <ranges>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using std::ranges::iota_view;

struct Vec2 {
    int x;
    int y;

    friend constexpr auto operator==(const Vec2& self, const Vec2& that) {
        return self.x == that.x && self.y == that.y;
    }
};

template <> struct std::hash<Vec2> {
    auto operator()(const Vec2& v) const {
        return std::hash<int>()(v.x) ^ std::hash<int>()(v.y);
    }
};

enum class Part : std::uint8_t { Part1, Part2 };

class Solution {
  public:
    Solution() = default;

    template <Part Part> auto solve() const {
        std::unordered_map<char, std::vector<Vec2>> nodes;

        for (const auto i : iota_view{0UZ, grid.size()}) {
            const auto& row = grid.at(i);
            for (const auto j : iota_view{0UZ, row.size()}) {
                if (grid[i][j] != '.') {
                    nodes[grid[i][j]].emplace_back(i, j);
                }
            }
        }

        const auto distance = [](Vec2 p1, Vec2 p2) {
            const auto dx = p1.x - p2.x;
            const auto dy = p1.y - p2.y;
            return std::sqrt((dx * dx) + (dy * dy));
        };
        const auto float_eq = []<typename Float>(Float that, Float equal_to)
            requires(std::is_floating_point_v<Float>)
        {
            const auto d = that - equal_to;
            static constexpr auto Epsilon =
                std::numeric_limits<Float>::epsilon();
            return (d > -Epsilon) && (d < Epsilon);
        };

        std::unordered_set<Vec2> set;

        for (const auto i : iota_view{0UZ, grid.size()}) {
            const auto& row = grid.at(i);
            for (const auto j : iota_view{0UZ, row.size()}) {
                for (const auto& [k, v] : nodes) {
                    for (const auto& v1 : v) {
                        for (const auto& v2 : v) {
                            if (v1 == v2) {
                                continue;
                            }

                            const Vec2 dv(v2.x - v1.x, v2.y - v1.y);
                            const Vec2 dc(static_cast<int>(i) - v1.x,
                                          static_cast<int>(j) - v1.y);

                            const Vec2 dcperp(-dc.y, dc.x);

                            if ((dcperp.x * dv.x + dcperp.y * dv.y) == 0) {
                                const Vec2 origin(i, j);
                                const auto d1 = distance(origin, v1);
                                const auto d2 = distance(origin, v2);

                                if constexpr (Part == Part::Part1) {
                                    if (float_eq(d1, d2 * 2) ||
                                        float_eq(d2, d1 * 2)) {
                                        set.emplace(i, j);
                                        break;
                                    }
                                } else if constexpr (Part == Part::Part2) {
                                    set.emplace(i, j);
                                }
                            }
                        }
                    }
                }
            }
        }

        return set.size();
    }

  private:
    std::vector<std::vector<char>> grid = Aoc::file_to_2d_array("input.txt");
};

auto main() -> int {
    Solution s;
    std::cout << "Part 1: " << s.solve<Part::Part1>() << '\n';
    std::cout << "Part 2: " << s.solve<Part::Part2>() << '\n';
}
