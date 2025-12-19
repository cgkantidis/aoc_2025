#include "utility.hpp"

#include <algorithm> // std::ranges::sort
#include <print> // std::println
#include <vector> // std::vector

static constexpr u64 BUFFER_SIZE = 80;

namespace
{
void
tests();
u64
get_num_fresh_fruit(std::vector<std::string> const &lines);
} // namespace

int
main(int argc, char const **argv) {
  tests();
  std::vector<std::string> lines = read_program_input(argc, argv);
  if (lines.empty()) {
    return 1;
  }
  std::println("{}", get_num_fresh_fruit(lines));
  return 0;
}

namespace
{
void
tests() {
  std::vector<std::string> const
      lines{"3-5", "10-14", "16-20", "12-18", "", "1", "5", "8", "11", "17", "32"};
  ASSERT(get_num_fresh_fruit(lines) == 14);
}

u64
get_num_fresh_fruit(std::vector<std::string> const &lines) {
  std::vector<std::pair<u64, u64>> fresh_ranges;
  for (auto const &line : lines) {
    if (line.empty()) {
      break;
    }

    auto min_max = split(line, "-");
    fresh_ranges.emplace_back(str_to_int<u64>(min_max[0]),
                              str_to_int<u64>(min_max[1]));
  }

  std::ranges::sort(
      fresh_ranges,
      [](std::pair<u64, u64> const &left, std::pair<u64, u64> const &right) {
        return left.first < right.first;
      });
  for (u64 i = 1; i < fresh_ranges.size(); ++i) {
    for (u64 j = 0; j < i; ++j) {
      fresh_ranges[i].first =
          std::max(fresh_ranges[i].first, fresh_ranges[j].second + 1);
    }
  }

  u64 num_fresh_fruit{};
  for (auto const &fresh_range : fresh_ranges) {
    if (fresh_range.first > fresh_range.second) {
      continue;
    }
    num_fresh_fruit += fresh_range.second - fresh_range.first + 1;
  }
  return num_fresh_fruit;
}
} // namespace
