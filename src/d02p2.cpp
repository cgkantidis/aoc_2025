#include "utility.hpp"

#include <print> // std::println
#include <vector> // std::vector

static constexpr u64 BUFFER_SIZE = 80;

namespace
{
void
tests();
bool
is_id_valid(std::string_view id);
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
  ASSERT(!is_id_valid("11"));
  ASSERT(!is_id_valid("22"));
  ASSERT(!is_id_valid("99"));
  ASSERT(!is_id_valid("111"));
  ASSERT(!is_id_valid("999"));
  ASSERT(!is_id_valid("1010"));
  ASSERT(!is_id_valid("1188511885"));
  ASSERT(!is_id_valid("222222"));
  ASSERT(!is_id_valid("446446"));
  ASSERT(!is_id_valid("38593859"));
  ASSERT(!is_id_valid("565656"));
  ASSERT(!is_id_valid("824824824"));
  ASSERT(!is_id_valid("2121212121"));
  std::vector<std::string> const lines{
      "11-22,95-115,998-1012,1188511880-1188511890,222220-222224,1698522-1698528,446443-446449,38593856-38593862,565653-565659,824824821-824824827,2121212118-2121212124"};
  ASSERT(get_sum_of_invalid_ids(lines) == 4174379265);
}

bool
is_id_valid(std::string_view id) {
  auto const len = id.size();
  for (u64 chunk_size = len / 2; chunk_size > 0; --chunk_size) {
    if (len % chunk_size != 0) {
      continue;
    }
    u64 num_chunks = len / chunk_size;
    u64 beg1 = 0;
    u64 beg2 = chunk_size;
    bool all_chunks_eq = true;
    for (u64 chunk = 0; chunk != num_chunks - 1; ++chunk) {
      bool eq = id.substr(beg1, chunk_size) == id.substr(beg2, chunk_size);
      if (!eq) {
        all_chunks_eq = false;
        break;
      }
      beg1 = beg2;
      beg2 += chunk_size;
    }
    if (all_chunks_eq) {
      return false;
    }
  }
  return true;
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
