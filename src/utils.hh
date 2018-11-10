namespace erraticamo
{
  namespace utils
  {
    double scale(double val, double src_min = -1.0, double src_max = 1.0,
                 double dst_min = 0.0, double dst_max = 1.0);

    std::int8_t binarize_color(std::int8_t val, std::int8_t treshold = 128);
  }
}
