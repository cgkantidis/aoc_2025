#include "matrix.hpp"
#include "utility.hpp"

#include <print> // std::println
#include <vector> // std::vector

static constexpr u64 BUFFER_SIZE = 80;

namespace
{
void
tests();
bool
is_paper_roll_accessible(Matrix<char> const &grid, u64 row, u64 col);
u64
get_total_paper_rolls(std::vector<std::string> const &lines);
} // namespace

int
main(int argc, char const **argv) {
  tests();
  std::vector<std::string> lines = read_program_input(argc, argv);
  if (lines.empty()) {
    return 1;
  }
  std::println("{}", get_total_paper_rolls(lines));
  return 0;
}

namespace
{
void
tests() {
  std::vector<std::string> const lines{"..@@.@@@@.",
                                       "@@@.@.@.@@",
                                       "@@@@@.@.@@",
                                       "@.@@@@..@.",
                                       "@@.@@@@.@@",
                                       ".@@@@@@@.@",
                                       ".@.@.@.@@@",
                                       "@.@@@.@@@@",
                                       ".@@@@@@@@.",
                                       "@.@.@@@.@."};
  ASSERT(get_total_paper_rolls(lines) == 13);
}

bool
is_paper_roll_accessible(Matrix<char> const &grid, u64 row, u64 col) {
  ASSERT(row > 0);
  ASSERT(col > 0);
  ASSERT(row < grid.rows() - 1);
  ASSERT(col < grid.cols() - 1);

  if (grid(row, col) != '@') {
    return false;
  }

  u64 total_rolls{};
  for (u64 r = row - 1; r < row + 2; ++r) {
    for (u64 c = col - 1; c < col + 2; ++c) {
      if (r == row && c == col) {
        continue;
      }
      if (grid(r, c) == '@') {
        ++total_rolls;
        if (total_rolls == 4) {
          return false;
        }
      }
    }
  }

  return true;
}

u64
get_total_paper_rolls(std::vector<std::string> const &lines) {
  Matrix<char> grid(lines.size() + 2, lines[0].size() + 2, '.');
  for (u64 row = 0; row < grid.rows() - 2; ++row) {
    for (u64 col = 0; col < grid.cols() - 2; ++col) {
      grid(row + 1, col + 1) = lines[row][col];
    }
  }
  u64 total_paper_rolls{};
  for (u64 row = 1; row < grid.rows() - 1; ++row) {
    for (u64 col = 1; col < grid.cols() - 1; ++col) {
      if (is_paper_roll_accessible(grid, row, col)) {
        ++total_paper_rolls;
      }
    }
  }
  return total_paper_rolls;
}
} // namespace
