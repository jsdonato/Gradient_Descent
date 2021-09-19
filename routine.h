#ifndef routine_h
#define routine_h

#include <armadillo>
#include <memory>
#include "gradient.h"
#include "constants.h"

class Routine {
public:
    virtual arma::mat run() const = 0;
    
    virtual ~Routine() = default;
    
protected:
    std::unique_ptr<Gradient> gradient = nullptr;
};

class SimpleRoutine : public Routine {
public:
    SimpleRoutine(std::unique_ptr<Gradient>& grad) : gradient(std::move(grad)) {}
    
    arma::mat run() const override {
        arma::mat grad = gradient->eval(starting_point);
        arma::mat x = starting_point - step_size * grad;
        while (arma::norm(grad, 2) > 0.00000001) {
            grad = gradient->eval(x);
            x = x - step_size * grad;
        }
        return x;
    }

private:
    std::unique_ptr<Gradient> gradient = nullptr;
};


#endif /* routine_h */
