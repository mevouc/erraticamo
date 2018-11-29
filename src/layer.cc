#include <algorithm>

#include "layer.hh"
#include "utils.hh"

#define DEFAULT_IMG_SCALE (1. / 8.)

erraticamo::Layer::Layer(size_t width, size_t height, double treshold)
  : layer_(width, height, CV_8UC1)
  , noise_(std::max(width, height))
{
  for (auto j = 0u; j < height; ++j)
  {
    for (auto i = 0u; i < width; ++i)
    {
      double noised = utils::scale(
          noise_.compute_octave_noise(i / (width * DEFAULT_IMG_SCALE),
                                      j / (height * DEFAULT_IMG_SCALE)));
      std::uint8_t color = static_cast<std::uint8_t>(noised * 255.0 + 0.5) % 255;
      layer_.at<std::uint8_t>(i, j) =
          utils::binarize_color(color, (1 - treshold) * 256);
    }
  }
}

std::uint8_t
erraticamo::Layer::at(size_t i, size_t j) const
{
  return layer_.at<std::uint8_t>(i, j);
}
