# Gradient_Descent

## Usage

This library is intended to support the research being conducted by Howard Levinson and myself (Joseph Donato) in mathematical optimization.  More specifically, we are investigating new methods for gradient descent.  This code is still in its infancy and as this research project progresses, more features and options will be added to the code.

To justify the templating that was used in this library we need to begin by noting that in most, if not, all gradient descent routines, the two parameters which are always present are the gradient of the function we wish to minimize and the starting point.  For this reason, the code is templated in the following form:
```
grad::Descent<GradientType, RoutineType> descent(...);
```
Currently, the code supports the `LinSysGradient` and `MatrixGradient` for `GradientType` and `SimpleRoutine` for `RoutineType`.  The `LinSysGradient` type is assoiated with the goal of solving `Ax = b` and the `MatrixGradient` type is associated with solving `AXB=C` where `X` is a diagonal matrix.  For the `MatrixGradient`, one of the expected parameters is a `double error_weight` which is denoted by `k` in the objective function `|AXB-C|_2^2+k|X_0|_2^2` which we are minimizing to solve the previously mentioned problem (Note, `X_0` is equivalent to `X` but with diagonal elements set to zero).  On the other hand, the `SimpleRoutine` type runs the algorithm/routine marked as "Simple" in the `gradient_descent_routines.pdf` file.  Other routine types such as Conjugate Gradient Descent are planned to be supported soon. 

## Requirements

The Armadillo C++ library for linear algebra is required to run this code.  Information regarding the documentation and installation of this library can be found at http://arma.sourceforge.net/. 
