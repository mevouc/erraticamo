#pragma once

# include <opencv2/core.hpp>
# include "noise.hh"

# define DEFAULT_TRESHOLD (1. / 2.)

namespace erraticamo
{
  class Layer
  {
  public:
    Layer(size_t width, size_t height, double treshold = DEFAULT_TRESHOLD);

    std::uint8_t at(size_t i, size_t j) const;

  private:
    cv::Mat layer_;
    Noise noise_;
  };
}
