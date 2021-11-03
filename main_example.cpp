#include "src/descent.h"

int main() {
    const arma::mat STARTING_POINT = {{-0.5, 0},
                                  {0, 0.5}};

    const double ERROR_WEIGHT = 15;

    const double STEP_SIZE = 0.00001;
    
    
    const arma::mat A = {{3, 4},
                         {6, 8}};

    const arma::mat B = {{7, 8},
                         {3, 5}};

    const arma::mat C = {{2, 7},
                         {4, 14}};
    
    grad::Descent<MatrixGradient, SimpleRoutine> descent(A, B, C, ERROR_WEIGHT, STARTING_POINT, STEP_SIZE);
    descent.Run();
    std::cout << "RESULT :" << descent.Result();
    return 0;
}
