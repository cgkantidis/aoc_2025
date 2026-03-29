#include "utility.hpp"

#include <algorithm> // std::ranges::sort
#include <cmath> // std::sqrt
#include <print> // std::println
#include <ranges> // std::views::take
#include <vector> // std::vector

namespace
{
void
tests();
u64
get_mul_last_jboxes_x(std::vector<std::string> const &lines);
} // namespace

int
main(int argc, char const **argv) {
  tests();
  std::vector<std::string> lines = read_program_input(argc, argv);
  if (lines.empty()) {
    return 1;
  }
  std::println("{}", get_mul_last_jboxes_x(lines));
  return 0;
}

namespace
{
void
tests() {
  std::vector<std::string> const lines{
      "162,817,812", "57,618,57",   "906,360,560", "592,479,940",
      "352,342,300", "466,668,158", "542,29,236",  "431,825,988",
      "739,650,466", "52,470,668",  "216,146,977", "819,987,18",
      "117,168,530", "805,96,715",  "346,949,466", "970,615,88",
      "941,993,340", "862,61,35",   "984,92,344",  "425,690,689"};
  ASSERT(get_mul_last_jboxes_x(lines) == 25272);
}

struct Location_3D
{
  u64 x;
  u64 y;
  u64 z;
};

struct Circuit
{
  std::vector<u64> jbox_indices;
};

u64
sqr_diff(u64 i, u64 j) {
  auto diff = i < j ? j - i : i - j;
  return diff * diff;
}

double
distance(Location_3D const &jbox1, Location_3D const &jbox2) {
  return std::sqrt(sqr_diff(jbox1.x, jbox2.x) + sqr_diff(jbox1.y, jbox2.y)
                   + sqr_diff(jbox1.z, jbox2.z));
}

u64
get_mul_last_jboxes_x(std::vector<std::string> const &lines) {
  std::vector<Location_3D> jboxes;
  jboxes.reserve(lines.size());
  for (auto const &line : lines) {
    auto coords = split(line, ",");
    jboxes.emplace_back(Location_3D{.x = str_to_int<u64>(coords[0]),
                                    .y = str_to_int<u64>(coords[1]),
                                    .z = str_to_int<u64>(coords[2])});
  }

  // find the distance between every pair of jboxes
  std::vector<std::tuple<double, u64, u64>> distances;
  distances.reserve((jboxes.size() - 1) * jboxes.size() / 2);
  for (u64 i = 0; i < jboxes.size() - 1; ++i) {
    for (u64 j = i + 1; j < jboxes.size(); ++j) {
      distances.emplace_back(distance(jboxes[i], jboxes[j]), i, j);
    }
  }

  std::ranges::sort(distances, [](auto const &l, auto const &r) {
    return std::get<0>(l) < std::get<0>(r);
  });

  std::vector<Circuit> circuits;
  u64 jbox1{};
  u64 jbox2{};
  for (auto const &dist : distances) {
    // check if the left jbox in the next shortest distance is in a circuit
    auto find_it1 = std::ranges::find_if(
        circuits,
        [idx = std::get<1>(dist)](Circuit const &circuit) {
          return std::ranges::find(circuit.jbox_indices, idx)
                 != circuit.jbox_indices.end();
        });
    // check if the right jbox in the next shortest distance is in a circuit
    auto find_it2 = std::ranges::find_if(
        circuits,
        [idx = std::get<2>(dist)](Circuit const &circuit) {
          return std::ranges::find(circuit.jbox_indices, idx)
                 != circuit.jbox_indices.end();
        });
    // if they are both in the same circuit, there is nothing to do
    if (find_it1 == find_it2 && find_it1 != circuits.end()) {
      continue;
    }
    if (find_it1 == circuits.end() && find_it2 == circuits.end()) {
      // if none of the two are in a circuit, create a new circuit
      circuits.emplace_back(std::vector{std::get<1>(dist), std::get<2>(dist)});
    } else if (find_it1 != circuits.end() && find_it2 != circuits.end()) {
      // if they are in different circuits, merge the circuits
      find_it1->jbox_indices.append_range(find_it2->jbox_indices);
      circuits.erase(find_it2);
    } else if (find_it1 != circuits.end()) {
      // one of the two is in a circuit while the other is not
      find_it1->jbox_indices.emplace_back(std::get<2>(dist));
    } else {
      find_it2->jbox_indices.emplace_back(std::get<1>(dist));
    }
    jbox1 = std::get<1>(dist);
    jbox2 = std::get<2>(dist);
  }

  return jboxes[jbox1].x * jboxes[jbox2].x;
}
} // namespace
