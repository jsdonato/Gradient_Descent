#include <stdio.h>
#include <memory>
#include "gradient.h"
#include "routine.h"

namespace grad {

template <typename T, typename S>
class Descent {
public:
    Descent(arma::cx_mat A, arma::cx_mat b, arma::cx_mat starting_point, double step_size) {
        gradient = std::make_shared<T>(A, b); 
	routine = std::make_shared<S>(gradient, starting_point, step_size);
    }

    Descent(arma::mat A, arma::mat b, arma::mat starting_point, double step_size) {
        gradient = std::make_shared<T>(arma::cx_mat(A, arma::zeros(A.n_rows, A.n_cols)), arma::cx_mat(b, arma::zeros(b.n_rows, b.n_cols))); 
	routine = std::make_shared<S>(gradient, arma::cx_mat(starting_point, arma::zeros(starting_point.n_rows, starting_point.n_cols)), step_size);
    }

    Descent(arma::cx_mat A, arma::cx_mat B, arma::cx_mat C, double error_weight, arma::cx_mat starting_point, double step_size) {
        gradient = std::make_shared<T>(A, B, C, error_weight);
	routine = std::make_shared<S>(gradient, starting_point, step_size);
    }

    Descent(arma::mat A, arma::mat B, arma::mat C, double error_weight, arma::mat starting_point, double step_size) {
        gradient = std::make_shared<T>(arma::cx_mat(A, arma::zeros(A.n_rows, A.n_cols)), arma::cx_mat(B, arma::zeros(B.n_rows, B.n_cols)), 
			               arma::cx_mat(C, arma::zeros(C.n_rows, C.n_cols)), error_weight);
	routine = std::make_shared<S>(gradient, arma::cx_mat(starting_point, arma::zeros(starting_point.n_rows, starting_point.n_cols)), step_size);
    }

    void Run() { routine->Run(); }
    
    
private:
    std::shared_ptr<T> gradient = nullptr;
    std::shared_ptr<S> routine = nullptr;
    
};

}
