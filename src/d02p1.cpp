#include "utility.hpp"

#include <print> // std::println
#include <vector> // std::vector

static constexpr u64 BUFFER_SIZE = 80;

namespace
{
void
tests();
u64
get_sum_of_invalid_ids(std::vector<std::string> const &lines);
} // namespace

int
main(int argc, char const **argv) {
  tests();
  std::vector<std::string> lines = read_program_input(argc, argv);
  if (lines.empty()) {
    return 1;
  }
  std::println("{}", get_sum_of_invalid_ids(lines));
  return 0;
}

namespace
{
void
tests() {
  std::vector<std::string> const lines{
      "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124"};
  ASSERT(get_sum_of_invalid_ids(lines) == 1227775554);
}

bool is_id_valid(std::string_view id) {
  auto const len = id.size();
  if (len % 2 == 1) {
    return true;
  }
  return id.substr(0, len / 2) != id.substr(len / 2);
}

u64
get_sum_of_invalid_ids(std::vector<std::string> const &lines) {
  auto const &line = lines.front();
  auto id_ranges = split(line, ",");
  u64 total{};

  for (auto const &id_range : id_ranges) {
    auto beg_end = split(id_range, "-");
    auto beg = str_to_int<u64>(beg_end[0]);
    auto end = str_to_int<u64>(beg_end[1]) + 1;
    for (u64 id = beg; id != end; ++id) {
      std::array<char, BUFFER_SIZE> id_str;
      auto result = std::to_chars(id_str.begin(), id_str.end(), id);
      *result.ptr = '\0';
      if (!is_id_valid(id_str.data())) {
        total += id;
      }
    }
  }
  return total;
}
} // namespace
