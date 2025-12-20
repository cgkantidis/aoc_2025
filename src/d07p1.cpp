#include "matrix.hpp"
#include "utility.hpp"

#include <print> // std::println
#include <vector> // std::vector

namespace
{
void
tests();
u64
get_num_splits(std::vector<std::string> const &lines);
} // namespace

int
main(int argc, char const **argv) {
  tests();
  std::vector<std::string> lines = read_program_input(argc, argv);
  if (lines.empty()) {
    return 1;
  }
  std::println("{}", get_num_splits(lines));
  return 0;
}

namespace
{
void
tests() {
  std::vector<std::string> const lines{".......S.......",
                                       "...............",
                                       ".......^.......",
                                       "...............",
                                       "......^.^......",
                                       "...............",
                                       ".....^.^.^.....",
                                       "...............",
                                       "....^.^...^....",
                                       "...............",
                                       "...^.^...^.^...",
                                       "...............",
                                       "..^...^.....^..",
                                       "...............",
                                       ".^.^.^.^.^...^.",
                                       "..............."};
  ASSERT(get_num_splits(lines) == 21);
}

u64
get_num_splits(std::vector<std::string> const &lines) {
  Matrix<char> grid(lines.size() + 2, lines[0].size() + 2, '.');
  for (u64 row = 0; row < grid.rows() - 2; ++row) {
    for (u64 col = 0; col < grid.cols() - 2; ++col) {
      grid(row + 1, col + 1) = lines[row][col];
    }
  }

  u64 num_splits{};
  for (u64 row = 1; row < grid.rows() - 1; ++row) {
    for (u64 col = 1; col < grid.cols() - 1; ++col) {
      if (grid(row - 1, col) == '.' || grid(row - 1, col) == '^') {
        continue;
      }
      if (grid(row, col) == '^') {
        ++num_splits;
        grid(row, col - 1) = grid(row, col + 1) = '|';
      } else {
        grid(row, col) = '|';
      }
    }
  }
  return num_splits;
}
} // namespace
