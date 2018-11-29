#include <boost/program_options.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>

#include "camo-generator.hh"

namespace po = boost::program_options;

int
run(const std::string& output, const std::size_t nb_layers, const bool verbose)
{
  if (verbose)
    std::cout << "Output file is: '" << output << "'" << std::endl;

  auto generator = erraticamo::CamoGenerator(nb_layers);

  auto img = generator();

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
    ("layers,l", po::value<std::size_t>(), "Number of color layers, 3 by default")
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

  if (vm.count("help"))
  {
    std::cout << desc << std::endl
              << "Examples:" << std::endl
              << "  erraticamo -o out.png --verbose" << std::endl
              << "  erraticamo -o example.tiff --layers 1" << std::endl;
    return 1;
  }

  const bool verbose = vm.count("verbose");

  std::string output("camo.tiff");
  if (vm.count("output"))
    output = vm["output"].as<std::string>();

  std::size_t nb_layers = 3;
  if (vm.count("layers"))
    nb_layers = vm["layers"].as<std::size_t>();

  return run(output, nb_layers, verbose);
}
