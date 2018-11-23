#pragma once

# include <cstdint>

namespace erraticamo
{
  namespace utils
  {
    double scale(double val, double src_min = -1.0, double src_max = 1.0,
                 double dst_min = 0.0, double dst_max = 1.0);

    std::uint8_t binarize_color(std::uint8_t val, std::uint8_t treshold = 128);
  }
}
