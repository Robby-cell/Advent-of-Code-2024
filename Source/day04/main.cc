#include <cstddef>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

struct Solution {
  struct Direction {
    int i;
    int j;
  };

  auto directed_has_xmas(std::size_t row, std::size_t column,
                         Direction direction) const {
    static constexpr char Expected[4]{'X', 'M', 'A', 'S'};
    auto index = 0UZ;

    for (auto i : std::ranges::iota_view{0, 4}) {
      if (row >= data.size() || column >= data[row].size()) {
        return false;
      }
      if (data[row][column] != Expected[index++]) {
        return false;
      }
      row += direction.i;
      column += direction.j;
    }
    return true;
  }

  auto count_xmas(std::size_t row, std::size_t col) const -> unsigned {
    if (data[row][col] != 'X') {
      return 0;
    }

    unsigned count{};

    static constexpr Direction Directions[]{{-1, 0},  {1, 0}, {0, -1}, {0, 1},
                                            {-1, -1}, {1, 1}, {-1, 1}, {1, -1}};

    for (const auto direction : Directions) {
      if (directed_has_xmas(row, col, direction)) {
        ++count;
      }
    }

    return count;
  }

  auto part1() const {
    unsigned total{};
    for (auto i : std::ranges::iota_view{0UZ, data.size()}) {
      const auto& row = data[i];
      for (auto j : std::ranges::iota_view{0UZ, row.size()}) {
        total += count_xmas(i, j);
      }
    }

    return total;
  }

  static auto
  to_array(std::string_view filename) -> std::vector<std::vector<char>> {
    std::vector<std::vector<char>> data;
    std::ifstream input(filename.data());
    //     std::istringstream input{R"(MMMSXXMASM
    // MSAMXMSMSA
    // AMXSXMAAMM
    // MSAMASMSMX
    // XMASAMXAMM
    // XXAMMXXAMA
    // SMSMSASXSS
    // SAXAMASAAA
    // MAMMMXMMMM
    // MXMXAXMASX)"};
    std::string line;

    while (std::getline(input, line)) {
      data.emplace_back(line.begin(), line.end());
    }

    return data;
  }

  std::vector<std::vector<char>> data = to_array("input.txt");
};

auto main() -> int {
  const Solution s;
  std::cout << "Part 1: " << s.part1() << '\n';
}
