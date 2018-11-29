#include "utils.hh"

double
erraticamo::utils::scale(double val, double src_min, double src_max,
                         double dst_min, double dst_max)
{
  val -= src_min;
  val *= (dst_max - dst_min) / (src_max - src_min);
  return dst_min + val;
}

std::uint8_t
erraticamo::utils::binarize_color(std::uint8_t val, std::uint8_t treshold)
{
  return val < treshold ? 0 : 255;
}

cv::Vec3b
erraticamo::utils::complementary_color(cv::Vec3b color)
{
  std::uint8_t r = 256 - color[0];
  std::uint8_t g = 256 - color[1];
  std::uint8_t b = 256 - color[2];

  return { r, g, b };
}
