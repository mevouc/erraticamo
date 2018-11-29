#include <boost/program_options.hpp>
#include <iostream>
#include <opencv2/imgcodecs.hpp>

#include "camo-generator.hh"

namespace po = boost::program_options;

int
run(const std::string& output, const bool verbose)
{
  if (verbose)
    std::cout << "Output file is: '" << output << "'" << std::endl;

  auto generator = erraticamo::CamoGenerator(3);

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
