#include "utility.hpp"

#include <algorithm> // std::minmax
#include <print> // std::println
#include <vector> // std::vector

namespace
{
void
tests();
u64
get_largest_area(std::vector<std::string> const &lines);
} // namespace

int
main(int argc, char const **argv) {
  tests();
  std::vector<std::string> lines = read_program_input(argc, argv);
  if (lines.empty()) {
    return 1;
  }
  std::println("{}", get_largest_area(lines));
  return 0;
}

namespace
{
void
tests() {
  std::vector<std::string> const lines{
      "7,1",
      "11,1",
      "11,7",
      "9,7",
      "9,5",
      "2,5",
      "2,3",
      "7,3",
  };
  ASSERT(get_largest_area(lines) == 50);
}

u64
get_area(Location const &loc1, Location const &loc2) {
  auto const [x, X] = std::minmax(loc1.col, loc2.col);
  auto const [y, Y] = std::minmax(loc1.row, loc2.row);
  return (X - x + 1) * (Y - y + 1);
}

u64
get_largest_area(std::vector<std::string> const &lines) {
  std::vector<Location> red_tiles;
  red_tiles.reserve(lines.size());
  for (auto const &line : lines) {
    auto const loc = split(line, ",");
    red_tiles.emplace_back(str_to_int<u64>(loc[1]), str_to_int<u64>(loc[0]));
  }

  u64 max_area{};
  for (u64 i = 0; i < red_tiles.size() - 1; ++i) {
    for (u64 j = i + 1; j < red_tiles.size(); ++j) {
      max_area = std::max(max_area, get_area(red_tiles[i], red_tiles[j]));
    }
  }
  return max_area;
}
} // namespace
