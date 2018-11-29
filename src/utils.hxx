#include <random>

#include "utils.hh"

template<typename Int>
Int
erraticamo::utils::uniform_random(Int max)
{
  static std::random_device r;
  static std::default_random_engine e(r());
  static std::uniform_int_distribution<Int> uniform_dist(0, max);

  return uniform_dist(e);
}
