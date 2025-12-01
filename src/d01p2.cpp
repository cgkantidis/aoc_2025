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
  {
    std::vector<std::string> const lines{"L50"};
    ASSERT(get_password(lines) == 1);
  }
  {
    std::vector<std::string> const lines{"L51"};
    ASSERT(get_password(lines) == 1);
  }
  {
    std::vector<std::string> const lines{"R50"};
    ASSERT(get_password(lines) == 1);
  }
  {
    std::vector<std::string> const lines{"R51"};
    ASSERT(get_password(lines) == 1);
  }
  {
    std::vector<std::string> const lines{"R49", "R2"};
    ASSERT(get_password(lines) == 1);
  }
  {
    std::vector<std::string> const
        lines{"L68", "L30", "R48", "L5", "R60", "L55", "L1", "L99", "R14", "L82"};
    ASSERT(get_password(lines) == 6);
  }
}

std::pair<char, u64>
parse_move(std::string const &move) {
  u64 clicks{};
  auto [ptr, ec] =
      std::from_chars(move.data() + 1, move.data() + move.size(), clicks);
  ASSERT(ec == std::errc());
  return {move[0], clicks};
}

u64
get_password(std::vector<std::string> const &lines) {
  // we need to count the number of times the dial points to zero, but not just
  // at the end of the rotation
  u64 times_over_zero{0};
  u64 dial_at{DIAL_START};
  for (std::string const &line : lines) {
    auto [dir, clicks] = parse_move(line);
    times_over_zero += clicks / DIAL_SIZE;
    clicks %= DIAL_SIZE;
    if (dir == 'L') {
      if (clicks >= dial_at && dial_at != 0) {
        ++times_over_zero;
      }
      dial_at = (DIAL_SIZE + dial_at - clicks) % DIAL_SIZE;
    } else {
      if (dial_at + clicks >= DIAL_SIZE) {
        ++times_over_zero;
      }
      dial_at = (dial_at + clicks) % DIAL_SIZE;
    }
  }
  return times_over_zero;
}
} // namespace
