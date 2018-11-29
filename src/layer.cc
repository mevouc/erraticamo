#include <algorithm>

#include "layer.hh"
#include "utils.hh"

erraticamo::Layer::Layer(size_t width, size_t height, double treshold)
  : layer_(width, height, CV_8UC1)
  , noise_(std::max(width, height))
{
  for (auto j = 0u; j < height; ++j)
  {
    for (auto i = 0u; i < width; ++i)
    {
      double noised = utils::scale(noise_.compute_octave_noise(i / (width / 8.),
                                                               j / (height / 8.)));
      std::uint8_t color = static_cast<std::uint8_t>(noised * 255.0 + 0.5) % 255;
      layer_.at<std::uint8_t>(i, j) = utils::binarize_color(color, treshold * 256);
    }
  }
}

std::uint8_t
erraticamo::Layer::at(size_t i, size_t j) const
{
  return layer_.at<std::uint8_t>(i, j);
}
