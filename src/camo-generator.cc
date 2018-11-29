#include <cassert>

#include "camo-generator.hh"
#include "utils.hh"

#define LOW_TRESHOLD (1. / 4.)
#define HIGH_TRESHOLD (1. / 2.)

erraticamo::CamoGenerator::CamoGenerator(size_t nb_layers, size_t width,
                                         size_t height, cv::Vec3b color)
  : nb_layers_(nb_layers)
  , background_color_(utils::complementary_color(color))
  , img_(width, height, CV_8UC3, background_color_)
  , colors_(nb_layers + 1)
{
  generate_colors_(color);
}


const cv::Mat&
erraticamo::CamoGenerator::operator()()
{
  generate_();
  return img_;
}

void
erraticamo::CamoGenerator::generate_()
{
  if (nb_layers_ == 0)
    return;

  const auto bottom_layer = Layer(img_.cols, img_.rows);
  add_layer_(bottom_layer);

  double interval = HIGH_TRESHOLD - LOW_TRESHOLD;
  double step = interval / (nb_layers_ - 1);

  for (auto i = 1u; i < nb_layers_; ++i)
  {
    double treshold = HIGH_TRESHOLD - step * (i - 1);
    add_layer_(Layer(img_.cols, img_.rows, treshold), i);
  }
}

void
erraticamo::CamoGenerator::add_layer_(const Layer layer, size_t layer_index)
{
  for (auto j = 0; j < img_.rows; ++j)
    for (auto i = 0; i < img_.cols; ++i)
      if (layer.at(i, j))
      {
        auto& pixel = img_.at<cv::Vec3b>(i, j);
        pixel = colors_.at(layer_index);
      }
}

void
erraticamo::CamoGenerator::generate_colors_(const cv::Vec3b base_color)
{
  (void)base_color;

  for (auto i = 0u; i < colors_.size(); ++i)
  {
    auto& color = colors_.at(i);
    color[0] = color[1] = color[2] = 80 * (i + 1); // TODO: use base color
  }
}
