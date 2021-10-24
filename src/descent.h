#include <stdio.h>
#include <memory>
#include "gradient.h"
#include "routine.h"

namespace grad {

template <typename T, typename S>
class Descent {
public:
    Descent(arma::mat A, arma::mat b, arma::mat starting_point, double step_size) {
        gradient = std::make_shared<T>(A, b); 
	routine = std::make_shared<S>(gradient, starting_point, step_size);
    }

    Descent(arma::mat A, arma::mat B, arma::mat C, double error_weight, arma::mat starting_point, double step_size) {
        gradient = std::make_shared<T>(A, B, C, error_weight);
	routine = std::make_shared<S>(gradient, starting_point, step_size);
    }

    void Run() { routine->Run(); }
    
    
private:
    std::shared_ptr<T> gradient = nullptr;
    std::shared_ptr<S> routine = nullptr;
    
};

}
