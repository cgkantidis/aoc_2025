#include "matrix.hpp"
#include "utility.hpp"

#include <algorithm> // std::ranges::fold_left
#include <print> // std::println
#include <vector> // std::vector

namespace
{
void
tests();
u64
get_num_timelines(std::vector<std::string> const &lines);
} // namespace

int
main(int argc, char const **argv) {
  tests();
  std::vector<std::string> lines = read_program_input(argc, argv);
  if (lines.empty()) {
    return 1;
  }
  std::println("{}", get_num_timelines(lines));
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
  ASSERT(get_num_timelines(lines) == 40);
}

u64
get_num_timelines(std::vector<std::string> const &lines) {
  auto const num_rows = lines.size();
  auto const num_cols = lines[0].size();

  // we keep track for each location, how many paths lead there
  Matrix<u64> paths(num_rows + 2, num_cols + 2, 0);

  [&paths, &lines, num_rows, num_cols]() {
    for (u64 row = 0; row < num_rows; ++row) {
      for (u64 col = 0; col < num_cols; ++col) {
        if (lines[row][col] == 'S') {
          paths(row + 1, col + 1) = 1;
          return;
        }
      }
    }
  }();

  for (u64 row = 1; row < num_rows + 1; ++row) {
    auto const l_row = row - 1;
    for (u64 col = 1; col < num_cols + 1; ++col) {
      auto const l_col = col - 1;
      // if there was a splitter in the above row, or empty space, there is
      // nothing to do
      if (paths(row - 1, col) == 0) {
        continue;
      }
      if (lines[l_row][l_col] == '^') {
        paths(row, col - 1) += paths(row - 1, col);
        paths(row, col + 1) += paths(row - 1, col);
      } else {
        paths(row, col) += paths(row - 1, col);
      }
    }
  }

  std::span last_row(paths.get_row(paths.rows() - 2), num_cols + 2);
  return std::ranges::fold_left(last_row, 0, std::plus<>());
}
} // namespace
