#include <boost/program_options.hpp>
#include <cmath>
#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <sstream>
#include <unordered_set>

namespace po = boost::program_options;

static std::int32_t p[512];
static std::int32_t permutation[] = { 151,160,137,91,90,15,
   131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
   190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
   88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
   77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
   102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
   135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
   5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
   223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
   129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
   251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
   49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
   138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
   };

static double Fade(double t)
{
  return t * t * t * (t * (t * 6 - 15) + 10);
}

static double Lerp(double t, double a, double b)
{
  return a + t * (b - a);
}

static double Grad(std::int32_t hash, double x, double y, double z)
{
  const std::int32_t h = hash & 15;
  const double u = h < 8 ? x : y;
  const double v = h < 4 ? y : h == 12 || h == 14 ? x : z;
  return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double
noise(double x, double y, double z)
{
  const std::int32_t X = static_cast<std::int32_t>(std::floor(x)) & 255;
  const std::int32_t Y = static_cast<std::int32_t>(std::floor(y)) & 255;
  const std::int32_t Z = static_cast<std::int32_t>(std::floor(z)) & 255;

  x -= std::floor(x);
  y -= std::floor(y);
  z -= std::floor(z);

  const double u = Fade(x);
  const double v = Fade(y);
  const double w = Fade(z);

  const std::int32_t A = p[X] + Y, AA = p[A] + Z, AB = p[A + 1] + Z;
  const std::int32_t B = p[X + 1] + Y, BA = p[B] + Z, BB = p[B + 1] + Z;

  return Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z),
    Grad(p[BA], x - 1, y, z)),
    Lerp(u, Grad(p[AB], x, y - 1, z),
    Grad(p[BB], x - 1, y - 1, z))),
    Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1),
    Grad(p[BA + 1], x - 1, y, z - 1)),
    Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1),
    Grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

double
noise(double x, double y)
{
  return noise(x, y, 0.0);
}

double
octave_noise(double x, double y, int octaves)
{
  double result = 0.0;
  double amp = 1.0;

  for (auto i = 0; i < octaves; ++i)
  {
    result += noise(x, y) * amp;
    x *= 2.0;
    y *= 2.0;
    amp *= 0.5;
  }

  return result;
}

std::uint8_t binarize(std::uint8_t val, std::uint8_t treshold)
{
  if (val < treshold)
    return 0;
  return 255;
}

int
run(const std::string& output, const bool verbose)
{
  if (verbose)
    std::cout << "Output file is: '" << output << "'" << std::endl;

  cv::Mat img(512, 512, CV_8UC3);

  for (int i=0; i < 256 ; i++)
    p[256+i] = p[i] = permutation[i];


  for (auto j = 0; j < 512; ++j)
  {
    for (auto i = 0; i < 512; ++i)
    {
      double noised = noise(i / (512.0 / 5), j / (512.0 / 5)) * 0.5 + 0.5;
//      std::cout << noised << ' ';
      std::uint8_t uint = (static_cast<std::uint8_t>(noised * 255.0 + 0.5)) % 255;
//      std::cout << static_cast<unsigned>(uint) << ' ';
      img.at<cv::Vec3b>(i, j)[0] = img.at<cv::Vec3b>(i, j)[1] = img.at<cv::Vec3b>(i, j)[2] = binarize(uint, 128);
    }
    std::cout << std::endl;
  }

  cv::imwrite(output, img);
  if (verbose)
    std::cout << "Output successfully written." << std::endl;

  return 0;
}

int
main(int argc, char* argv[])
{
  std::stringstream intro;
  intro << "Does things with perlin noise." << std::endl
        << std::endl << "Usage";
  po::options_description desc(intro.str());

  desc.add_options()
    ("help,h", "Display this message")
    ("output,o", po::value<std::string>(), "Output image")
    ("verbose,v", "Enable useful information output")
    ;

  po::variables_map vm;
  try
  {
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << std::endl
              << desc << std::endl;
    return 1;
  }

  std::string output("camo.tiff");

  const bool verbose = vm.count("verbose");

  if (vm.count("help"))
  {
    std::cout << desc << std::endl
              << "Examples:" << std::endl
              << "  erraticamo -o out.png --verbose" << std::endl
              << "  erraticamo -o example.tiff" << std::endl;
    return 1;
  }

  if (vm.count("output"))
    output = vm["output"].as<std::string>();

  return run(output, verbose);
}
