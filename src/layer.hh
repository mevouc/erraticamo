#pragma once

# include <opencv2/core.hpp>
# include "noise.hh"

namespace erraticamo
{
  class Layer
  {
  public:
    Layer(size_t width, size_t height, double treshold = 0.5);

    std::uint8_t at(size_t i, size_t j) const;

  private:
    cv::Mat layer_;
    Noise noise_;
  };
}
