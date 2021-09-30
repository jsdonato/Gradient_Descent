# Gradient_Descent

## Usage

This code is intended to support the research being conducted by Howard Levinson and myself (Joseph Donato) in mathematical optimization.  More specifically, we are investigating new methods for gradient descent.  This code is still in its infancy and as this research project progresses, more features and options will be added to the code.

### Command Line Flags

| Flag | Description |
| --- | --- |
| `-p`,`--problem` |A string is required after this flag which specifies the type of problem you wish to solve.|
|`-r`, `--routine`|A string is required after this flag which specifies the type gradient descent routine you wish to employ.|

### Flag Options

| `-p` option |Option description for `-p`|
| --- | --- |
| `linsys` |This problem is concerned with minimizing `[Ax-b]_{2}^2` where `A` and `b` are entered in the `input.h` file.|
| `matrixsys`|This problem is concerned with minimizing `[AXB-C]_{2}^2+[X_0]_2^2` where `X_0` is equivalent to `X` except that `X_0` is all zeros along the diagonal. `A`,`B` and `C` are entered in the `input.h` file.|

| `-r` option |Option description for `-r`|
| --- | --- |
| `simple` |This routine is the simplest form of gradient descent.  The step size and starting point can be entered in the `constants.h` file.  A description of this routine can be found in the `gradient_descent_routines.pdf` file.|

## Requirements

The Armadillo C++ library for linear algebra is required to run this code.  Information regarding the documentation and installation of this library can be found at http://arma.sourceforge.net/. 
