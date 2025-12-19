#include "utility.hpp"

#include <algorithm> // std::ranges::sort
#include <print> // std::println
#include <ranges> // std::ranges::take
#include <vector> // std::vector

namespace
{
void
tests();
u64
get_grand_total(std::vector<std::string> const &lines);
} // namespace

int
main(int argc, char const **argv) {
  tests();
  std::vector<std::string> lines = read_program_input(argc, argv);
  if (lines.empty()) {
    return 1;
  }
  std::println("{}", get_grand_total(lines));
  return 0;
}

namespace
{
void
tests() {
  std::vector<std::string> const lines{"123 328  51 64 ",
                                       " 45 64  387 23 ",
                                       "  6 98  215 314",
                                       "*   +   *   +  "};
  ASSERT(get_grand_total(lines) == 4277556);
}

u64
get_grand_total(std::vector<std::string> const &lines) {
  auto const operands =
      std::ranges::to<std::vector<std::vector<u64>>>(std::views::transform(
          std::views::take(lines, static_cast<long>(lines.size() - 1)),
          [](std::string const &line) {
            return std::ranges::to<std::vector<u64>>(
                std::views::transform(split(line, " "), str_to_int<u64>));
          }));
  auto const operators = split(lines.back(), " ");
  u64 grand_total{};
  for (u64 col = 0; col < operators.size(); ++col) {
    u64 total = 0;
    if (operators[col] == "*") {
      total = 1;
    }
    for (auto const &operands_row : operands) {
      if (operators[col] == "+") {
        total += operands_row[col];
      } else {
        total *= operands_row[col];
      }
    }
    grand_total += total;
  }
  return grand_total;
}
} // namespace
