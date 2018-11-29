#pragma once

# include <opencv2/core.hpp>

# include "layer.hh"

# define DEFAULT_NB_LAYERS (1)
# define DEFAULT_IMG_WIDTH (512)
# define DEFAULT_IMG_HEIGHT (512)
# define DEFAULT_COLOR { 255, 255, 255 }

namespace erraticamo
{
  class CamoGenerator
  {
  public:
    CamoGenerator(size_t nb_layers = DEFAULT_NB_LAYERS,
                  size_t width = DEFAULT_IMG_WIDTH,
                  size_t height = DEFAULT_IMG_HEIGHT,
                  cv::Vec3b color = DEFAULT_COLOR);

    const cv::Mat& operator()();

  private:
    void generate_();

    void add_layer_(const Layer layer, size_t layer_index = 0);
    
    void generate_colors_(const cv::Vec3b base_color);

  private:
    const size_t nb_layers_;
    const cv::Vec3b background_color_;
    cv::Mat img_;
    std::vector<cv::Vec3b> colors_;
  };
}
