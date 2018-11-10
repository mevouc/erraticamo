#pragma once

# define DEFAULT_OCTAVES 3

namespace erraticamo
{
  class Noise
  {
  public:
    Noise(size_t size = 512);
    
    double compute_noise(double x, double y);

    double compute_octave_noise(double x, double y,
                                int octaves = DEFAULT_OCTAVES);
  private:
    static double s_fade_(double t);
    static double s_lerp_(double t, double a, double b);
    static double s_grad_(std::int32_t hash, double x, double y);

    void permut_to_p_();
    void reseed_permutations_();

    size_t size_;
    std::int32_t p_[];
    std::int32_t permutations_[];
  }
}
