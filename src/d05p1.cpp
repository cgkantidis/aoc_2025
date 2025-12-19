#include "utility.hpp"

#include <algorithm> // std::ranges::sort
#include <print> // std::println
#include <vector> // std::vector

static constexpr u64 BUFFER_SIZE = 80;

namespace
{
void
tests();
bool
is_item_fresh(std::vector<std::pair<u64, u64>> const &fresh_ranges, u64 item_id);
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
  ASSERT(get_num_fresh_fruit(lines) == 3);
}

bool
is_item_fresh(std::vector<std::pair<u64, u64>> const &fresh_ranges, u64 item_id) {
  for (auto const &fresh_range : fresh_ranges) {
    if (item_id < fresh_range.first) {
      return false;
    }
    if (item_id > fresh_range.second) {
      continue;
    }
    return true;
  }
  return false;
}

u64
get_num_fresh_fruit(std::vector<std::string> const &lines) {
  bool reading_ranges = true;
  std::vector<std::pair<u64, u64>> fresh_ranges;
  u64 num_fresh_fruit{};
  for (auto const &line : lines) {
    if (line.empty()) {
      reading_ranges = false;
      std::ranges::sort(fresh_ranges,
                        [](std::pair<u64, u64> const &left,
                           std::pair<u64, u64> const &right) {
                          return left.first < right.first;
                        });
      continue;
    }

    if (reading_ranges) {
      auto min_max = split(line, "-");
      fresh_ranges.emplace_back(str_to_int<u64>(min_max[0]),
                                str_to_int<u64>(min_max[1]));
      continue;
    }

    u64 item_id = str_to_int<u64>(line);
    if (is_item_fresh(fresh_ranges, item_id)) {
      ++num_fresh_fruit;
    }
  }
  return num_fresh_fruit;
}
} // namespace
