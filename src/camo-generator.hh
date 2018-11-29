#pragma once

# include <opencv2/core.hpp>

# include "layer.hh"

namespace erraticamo
{
  class CamoGenerator
  {
  public:
    CamoGenerator(size_t nb_layers = 1, size_t width = 512, size_t height = 512,
                  cv::Vec3b color = { 255, 255, 255 });

    const cv::Mat& operator()();

  private:
    void generate_();

    void add_layer_(const Layer layer, size_t layer_index = 0);
    
    void generate_colors_(const cv::Vec3b base_color);

  private:
    const size_t nb_layers_;
    cv::Mat img_;
    std::vector<cv::Vec3b> colors_;
  };
}
