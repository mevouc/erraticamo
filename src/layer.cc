#include <algorithm>

#include "layer.hh"

erraticamo::Layer::Layer(size_t width, size_t height, double treshold)
  : layer_(width, height, CV_8UC1)
  , noise_(std::max(width, height))
{
  for (auto j = 0; j < height; ++j)
  {
    for (auto i = 0; i < width; ++i)
    {
      double noised = utils::scale(noise_.compute_octave_noise(i / (width / 8),
                                                               j / (height / 8)));
      std::uint8_t color = static_cast<std::uint8_t>(noised * 255.0 + 0.5) % 255;
      img.at<cv::Vec1b>(i, j)[0] = utils::binarize_color(uint, treshold * 256);
    }
  }
}
