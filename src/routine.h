#ifndef routine_h
#define routine_h

#include <armadillo>
#include <memory>
#include "gradient.h"

class Routine {
public:
    Routine(std::shared_ptr<Gradient> gradient_, arma::mat starting_point_, double step_size_) : 
	          gradient(std::move(gradient_)), starting_point(starting_point_), step_size(step_size_) {}
    
    virtual arma::mat Run() const = 0;
    
    virtual ~Routine() = default;
    
protected:
    std::shared_ptr<Gradient> gradient = nullptr;
    arma::mat starting_point;
    double step_size;
};

class SimpleRoutine : public Routine {
public:
    SimpleRoutine(std::shared_ptr<Gradient> gradient_, arma::mat starting_point_, double step_size_) : 
	          Routine(gradient_, starting_point_, step_size_) {}
    
    arma::mat Run() const override {
        arma::mat grad = gradient->gradEval(starting_point);
        arma::mat x = starting_point - step_size * grad;
        while (arma::norm(grad, 2) > 0.00000001) {
            grad = gradient->gradEval(x);
            x = x - step_size * grad;
            std::cout << x << std::endl << std::endl;
        }
        return x;
    }
};


#endif /* routine_h */
