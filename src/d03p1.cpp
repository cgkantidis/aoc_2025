#include "utility.hpp"

#include <algorithm> // std::ranges::fold_left
#include <print> // std::println
#include <vector> // std::vector

static constexpr u64 BUFFER_SIZE = 80;

namespace
{
void
tests();
u64
get_max_joltage(std::string_view battery_bank);
u64
get_total_joltage(std::vector<std::string> const &lines);
} // namespace

int
main(int argc, char const **argv) {
  tests();
  std::vector<std::string> lines = read_program_input(argc, argv);
  if (lines.empty()) {
    return 1;
  }
  std::println("{}", get_total_joltage(lines));
  return 0;
}

namespace
{
void
tests() {
  ASSERT(get_max_joltage("987654321111111") == 98);
  ASSERT(get_max_joltage("811111111111119") == 89);
  ASSERT(get_max_joltage("234234234234278") == 78);
  ASSERT(get_max_joltage("818181911112111") == 92);
  std::vector<std::string> const lines{"987654321111111",
                                       "811111111111119",
                                       "234234234234278",
                                       "818181911112111"};
  ASSERT(get_total_joltage(lines) == 357);
}

u64
get_max_joltage(std::string_view battery_bank) {
  u64 const num_digits = 2;
  std::array<char, num_digits + 1> max_joltage_str{};
  auto const *beg_it = battery_bank.begin();
  auto const *end_it = std::prev(battery_bank.end(), num_digits - 1);
  for (u64 i = 0; i < num_digits; ++i) {
    auto const *max_it = std::max_element(beg_it, end_it);
    max_joltage_str[i] = *max_it;
    beg_it = std::next(max_it);
    std::advance(end_it, 1);
  }

  u64 max_joltage{};
  std::from_chars(max_joltage_str.begin(), max_joltage_str.end(), max_joltage);
  return max_joltage;
}

u64
get_total_joltage(std::vector<std::string> const &lines) {
  return std::ranges::fold_left(lines,
                                0ULL,
                                [](u64 total, std::string const &line) {
                                  return total + get_max_joltage(line);
                                });
}
} // namespace
