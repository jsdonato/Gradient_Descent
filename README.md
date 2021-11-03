# Gradient_Descent

## Usage

This library is intended to support the research being conducted by Howard Levinson and myself (Joseph Donato) in mathematical optimization.  More specifically, we are investigating new methods for gradient descent.  This code is still in its infancy and as this research project progresses, more features and options will be added to the code.

To justify the templating that was used in this library we need to begin by noting that in most, if not, all gradient descent routines, the two parameters which are always present are the gradient of the function we wish to minimize and the starting point.  For this reason, the code is templated in the following form:
```
grad::Descent<GradientType, RoutineType> descent(...);
```

### GradientType
| Allowed type for GradientType  | Possible Input for Descent object | Description |
| ------------- | ------------- | ------------- |
| `LinSysGradient` | `grad::Descent<LinSysGradient, RoutineType>(arma::cx_mat A, arma::cx_mat b, arma::cx_mat starting_point, double step_size)`, `grad::Descent<LinSysGradient, RoutineType>(arma::mat A, arma::mat b, arma::mat starting_point, double step_size)` | Solves `Ax=b` by minimizing `[Ax-b]_2^2`.|
| `MatrixGradient` | `grad::Descent<MatrixGradient, RoutineType>(arma::cx_mat A, arma::cx_mat B, arma::cx_mat C, double error_weight, arma::cx_mat starting_point, double step_size)`, `grad::Descent<MatrixGradient, RoutineType>(arma::mat A, arma::mat B, arma::mat C, double error_weight, arma::mat starting_point, double step_size)` | Solves `AXB=C` where `X` is a diagonal matrix by minimizing `[AXB-C]_2^2+k[X_0]_2^2` (Note, `X_0` is equivalent to `X` but with diagonal elements set to zero).|

### RoutineType
The allowed types for `RoutineType` are currently {`SimpleRoutine`, `ExperimentalRoutine`} and the descriptions of them can be found in `gradient_descent_routines.pdf` 

## Documentation
| Feature  | Functionality |
| ------------- | ------------- |
| `grad::Descent<GradientType, RoutineType> descent(...)` | Declares a `Descent` object  |
| `Run()` | Runs descent routine  |
| `Result()` | Returns the result which is of type complex matrix (`arma::cx_mat`).  If the inputs were real matricies (`arma::mat`) then the imaginary part of the result is the zero matrix. |

## Requirements

The Armadillo C++ library for linear algebra is required to run this code.  Information regarding the documentation and installation of this library can be found at http://arma.sourceforge.net/. 
