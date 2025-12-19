#include "utility.hpp"

#include <algorithm>
#include <print> // std::println
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
  ASSERT(get_grand_total(lines) == 3263827);
}

u64
get_grand_total(std::vector<std::string> const &lines) {
  u64 col = 0;
  auto const num_operands = lines.size() - 1;
  auto const operators = split(lines.back(), " ");
  auto operators_it = operators.begin();

  u64 grand_total{};
  std::vector<u64> operands;
  std::string buffer{};
  while (col < lines[0].size()) {
    bool is_separator =
        std::ranges::all_of(lines, [col](std::string const &line) {
          return line[col] == ' ';
        });

    if (is_separator) {
      grand_total +=
          *operators_it == "+"
              ? std::ranges::fold_left(operands, 0ULL, std::plus<u64>{})
              : std::ranges::fold_left(operands, 1ULL, std::multiplies<u64>{});
      ++operators_it;
      ++col;
      operands.clear();
      continue;
    }

    for (u64 row = 0; row < num_operands; ++row) {
      if (lines[row][col] == ' ') {
        continue;
      }
      buffer += lines[row][col];
    }
    operands.emplace_back(str_to_int<u64>(buffer));
    buffer.clear();
    ++col;
  }
  grand_total +=
      *operators_it == "+"
          ? std::ranges::fold_left(operands, 0ULL, std::plus<u64>{})
          : std::ranges::fold_left(operands, 1ULL, std::multiplies<u64>{});
  return grand_total;
}
} // namespace
