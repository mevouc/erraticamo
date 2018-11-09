# erraticamouflage

Procedurally generated camouflage textures.

## Options

- `--size`
- `--output`
- `--input-palette`
- `--depth` (nb color layers above background)
- `--color` (intermediate color, other colors will be chosen "around" it)
- `--antialiasing`
- `--help`
- `--verbose`
- `--parallel` (or no-parallel)

## Architecture

- Possible optimization : parse the input image one time only, "testing" layer
  one after the other for each pixel

### Main function

- Parse options
- Instantiate Generator
- Triggers generation
- Write out result

### Generator

- Create N layers, assign seed to each one (possibly parallel)
- Compose Layers into one image/matrix
  - Assign colors to each layer

### Layer

- Black & white
- Take as input the size, and the "amount" of color of this layer
