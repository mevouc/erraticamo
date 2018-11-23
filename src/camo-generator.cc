#include <cassert>

#include "camo-generator.hh"

erraticamo::CamoGenerator::CamoGenerator(size_t nb_layers, size_t width,
                                         size_t height, cv::Vec3b color)
  : nb_layers_(nb_layers)
  , img_(width, height, CV_8UC3, color)
  , color_(color)
{}

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

  for (auto i = 1u; i < nb_layers_; ++i)
    continue; // TODO: add layers
}

void
erraticamo::CamoGenerator::add_layer_(const Layer layer)
{
  for (auto j = 0; j < img_.rows; ++j)
    for (auto i = 0; i < img_.cols; ++i)
    {
      if (layer.at(i, j))
        img_.at<cv::Vec3b>(i, j) = color_;
    }
}
