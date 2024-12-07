#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using i64 = std::int64_t; // NOLINT

using OpRepr = std::uint8_t;
enum class Operator : OpRepr { Add, Mul };
auto Increment(Operator& op) -> Operator& {
    op = static_cast<Operator>(static_cast<OpRepr>(op) + 1);
    return op;
}

auto CreateOperatorList(std::size_t size) {
    std::vector<Operator> ops(size);
    for (auto& op : ops) {
        op = Operator::Add;
    }

    return ops;
}

auto Eval(i64 lhs, i64 rhs, Operator op) -> i64 {
    switch (op) {
    case Operator::Add: {
        return lhs + rhs;
    }
    case Operator::Mul: {
        return lhs * rhs;
    }
    }
    std::unreachable();
}

struct Solution {
    struct Equation {
      public:
        i64 result;
        std::vector<i64> parts;

        auto IsPossiblyTruePart1() const {
            static constexpr auto Begin = Operator::Add;
            static constexpr auto End =
                static_cast<Operator>(static_cast<OpRepr>(Operator::Mul) + 1);

            auto ops = CreateOperatorList(parts.size() - 1);
            auto good = [](const auto& ops) {
                return std::all_of(ops.begin(), ops.end(), [](auto op) {
                    return static_cast<OpRepr>(op) <=
                           static_cast<OpRepr>(Operator::Mul);
                });
            };

            while (good(ops)) {
                // change the state and recalc the value
            }
        }

        static auto FromString(const std::string& str) -> Equation {
            std::istringstream iss{str};
            std::string result_str;

            iss >> result_str;
            result_str.pop_back(); // remove colon
            i64 result = std::stoll(result_str);

            i64 num;
            std::vector<i64> parts;
            while (iss >> num) {
                parts.push_back(num);
            }

            return {result, std::move(parts)};
        }

        Equation(i64 result, std::vector<i64> parts)
            : result(result), parts(std::move(parts)) {}

        friend auto operator<<(std::ostream& os, const Equation& e)
            -> decltype(auto) {
            os << e.result << ": ";
            auto idx = 0UZ;
            for (auto n : e.parts) {
                os << n << (++idx == e.parts.size() ? "" : " ");
            }
            return os;
        }
    };

    static auto EquationsFromFileName(auto&& file) -> std::vector<Equation> {
        std::ifstream fs{file};
        return EquationsFromStream(fs);
    }

    static auto EquationsFromStream(std::istream& is) -> std::vector<Equation> {
        std::vector<Equation> equations;

        std::string line;
        while (std::getline(is, line)) {
            equations.emplace_back(Equation::FromString(line));
        }

        return equations;
    }

    Solution() : Solution(EquationsFromFileName("input.txt")) {}

  private:
    friend auto operator<<(std::ostream& os, const Solution& s)
        -> decltype(auto) {
        for (const auto& equation : s.equations_) {
            os << equation << '\n';
        }
        return os;
    }

    constexpr explicit Solution(std::vector<Equation> equations)
        : equations_(std::move(equations)) {}

    std::vector<Equation> equations_;
};

auto main() -> int {
    Solution s;
    std::cout << s;
}
