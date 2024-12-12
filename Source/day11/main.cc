#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <istream>
#include <ranges>
#include <span>
#include <vector>

class Solution {
  public:
    Solution() = default;

    auto split_stones(std::span<const std::int64_t> stones) const {
        std::vector<std::int64_t> out;

        for (auto s : stones) {
            // rule 1: 0 replaces with 1
            if (s == 0) {
                out.emplace_back(1);
                continue;
            }

            // rule 2: even number of digits is split
            auto digits = digit_count(s);
            if (digits % 2 == 0) {
                auto factor =
                    static_cast<std::int64_t>(std::pow(10, digits / 2));
                auto left = s / factor;
                auto right = s % factor;
                out.emplace_back(left);
                out.emplace_back(right);
                continue;
            }

            out.emplace_back(s * 2024);
        }

        return out;
    }

    auto blinks(auto blink_count) const {
        auto stones = input;
        for (auto i :
             std::ranges::iota_view{decltype(blink_count)(0), blink_count}) {
            stones = split_stones(stones);
        }
        return stones.size();
    }

    auto part1() const { return blinks(25); }
    auto part2() const { return blinks(75); }

  private:
    auto digit_count(std::int64_t n) const -> std::size_t {
        auto count{0UZ};
        while (n > 0) {
            ++count;
            n /= 10;
        }
        return count;
    }

    static auto make_integer_vec_from_stream(std::istream& is)
        -> std::vector<std::int64_t> {
        std::vector<std::int64_t> output;
        for (std::int64_t n; is >> n;) {
            output.emplace_back(n);
        }
        return output;
    }

    template <class Path>
    static auto make_integer_vec_from_file(Path&& path)
        -> std::vector<std::int64_t> {
        std::ifstream is{path};
        return make_integer_vec_from_stream(is);
    }

    std::vector<std::int64_t> input = make_integer_vec_from_file("input.txt");
    // std::vector<std::int64_t> input = make_integer_vec_from_file("test.txt");
};

auto main() -> int {
    Solution s;
    std::cout << "Part 1: " << s.part1() << '\n';
    std::cout << "Part 2: " << s.part2() << '\n';
}
