#pragma once

# include <opencv2/core.hpp>

namespace erraticamo
{
  class Layer
  {
  public:
    Layer(size_t width, size_t height, double treshold = 0.5);

  private:
    const cv::Mat layer_;
    const Noise noise_;
  }
}
