#include "utility.hpp"

#include <print> // std::println
#include <vector> // std::vector

static constexpr u64 DIAL_START{50};
static constexpr u64 DIAL_SIZE{100};

namespace
{
void
tests();
u64
get_password(std::vector<std::string> const &lines);
} // namespace

int
main(int argc, char const **argv) {
  tests();
  std::vector<std::string> lines = read_program_input(argc, argv);
  std::println("{}", get_password(lines));
  return 0;
}

namespace
{
void
tests() {
  std::vector<std::string> const
      lines{"L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82"};
  ASSERT(get_password(lines) == 3);
}

u64
turns_to_right(std::string const &move) {
  u64 turns{};
  auto [ptr, ec] = std::from_chars(move.data() + 1, move.data() + move.size(), turns);
  turns %= DIAL_SIZE;
  ASSERT(ec == std::errc());
  if (move[0] == 'L') {
    turns = DIAL_SIZE - turns;
  }
  return turns;
}

u64
get_password(std::vector<std::string> const &lines) {
  u64 times_at_zero{0};
  u64 dial_at{DIAL_START};
  for (std::string const &line : lines) {
    dial_at += turns_to_right(line);
    dial_at %= DIAL_SIZE;
    if (dial_at == 0) {
      ++times_at_zero;
    }
  }
  return times_at_zero;
}
} // namespace
