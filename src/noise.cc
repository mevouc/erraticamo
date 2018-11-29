#include <cmath>

#include "noise.hh"
#include "utils.hh"

erraticamo::Noise::Noise(size_t size)
  : size_((size / 2) * 2)
  , p_(size_)
  , permutations_(size_ / 2)
{
  reseed_permutations_();
}

double
erraticamo::Noise::compute_noise(double x, double y)
{
  const std::int32_t X = static_cast<std::int32_t>(std::floor(x)) & 255;
  const std::int32_t Y = static_cast<std::int32_t>(std::floor(y)) & 255;

  x -= std::floor(x);
  y -= std::floor(y);

  const double u = s_fade_(x);
  const double v = s_fade_(y);

  const std::int32_t A = p_[X] + Y;
  const std::int32_t AA = p_[A];
  const std::int32_t AB = p_[A + 1];

  const std::int32_t B = p_[X + 1] + Y;
  const std::int32_t BA = p_[B];
  const std::int32_t BB = p_[B + 1];

  return s_lerp_(v, s_lerp_(u, s_grad_(p_[AA], x, y),
                               s_grad_(p_[BA], x - 1, y)),
                    s_lerp_(u, s_grad_(p_[AB], x, y - 1),
                               s_grad_(p_[BB], x - 1, y - 1)));
}


double
erraticamo::Noise::compute_octave_noise(double x, double y, int octaves)
{
  double result = 0.0;
  double amp = 1.0;

  for (auto i = 0; i < octaves; ++i)
  {
    result += compute_noise(x, y) * amp;
    x *= 2.0;
    y *= 2.0;
    amp *= 0.5;
  }

  return result;
}

void
erraticamo::Noise::permut_to_p_()
{
  for (auto i = 0u; i < size_ / 2 ; ++i)
    p_[size_ / 2 + i] = p_[i] = permutations_[i];
}

void
erraticamo::Noise::reseed_permutations_()
{
//  std::random_device r;
//  std::default_random_engine e(r());
//  std::uniform_int_distribution<std::int32_t> uniform_dist(0, size_ / 2);

  for (auto i = 0u; i < size_ / 2; ++i)
    permutations_[i] = utils::uniform_random<std::int32_t>(size_ / 2);

  permut_to_p_();
}

double
erraticamo::Noise::s_fade_(double t)
{
  return t * t * t * (t * (t * 6 - 15) + 10);
}

double
erraticamo::Noise::s_lerp_(double t, double a, double b)
{
  return a + t * (b - a);
}

double
erraticamo::Noise::s_grad_(std::int32_t hash, double x, double y)
{
  const std::int32_t h = hash & 15;
  const double u = h < 8 ? x : y;
  const double v = h < 4 ? y : h == 12 || h == 14 ? x : 0;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}
