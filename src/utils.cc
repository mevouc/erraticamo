#include "utils.hh"

double
erraticamo::utils::scale(double val, double src_min, double src_max,
                         double dst_min, double dst_max)
{
  val -= src_min;
  val *= (dst_max - dst_min) / (src_max - src_min);
  return dst_min + val;
}

std::int8_t
erraticamo::utils::binarize_color(std::int8_t val, std::int8_t treshold)
{
  return val < treshold ? 0 : 255;
}
