#ifndef routine_h
#define routine_h

#include <armadillo>
#include <memory>
#include <limits>
#include "gradient.h"

class Routine {
public:
    Routine(std::shared_ptr<Gradient> gradient_, arma::cx_mat starting_point_, double step_size_) : 
	          gradient(std::move(gradient_)), starting_point(starting_point_), step_size(step_size_) {}
    
    void print(const arma::cx_mat& Mat) const {
        if (arma::imag(Mat).is_zero(arma::datum::eps)) {
	    std::cout << arma::real(Mat) << std::endl;
	}
	else {
	    std::cout << Mat << std::endl; 
	}
    }

    virtual arma::cx_mat Run() const = 0;
    
    virtual ~Routine() = default;
    
protected:
    std::shared_ptr<Gradient> gradient = nullptr;
    arma::cx_mat starting_point;
    double step_size;
};

class SimpleRoutine : public Routine {
public:
    SimpleRoutine(std::shared_ptr<Gradient> gradient_, arma::cx_mat starting_point_, double step_size_) : 
	          Routine(gradient_, starting_point_, step_size_) {}
    
    arma::cx_mat Run() const override {
        arma::cx_mat grad = gradient->gradEval(starting_point);
        arma::cx_mat x = starting_point - step_size * grad;
        while (arma::norm(grad, 2) > 0.00000001) {
            grad = gradient->gradEval(x);
            x = x - step_size * grad;
            print(x);
        }
        return x;
    }
};


#endif /* routine_h */
