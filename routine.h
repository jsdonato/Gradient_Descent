#ifndef routine_h
#define routine_h

#include <armadillo>
#include <memory>
#include "gradient.h"
#include "constants.h"

class Routine {
public:
    virtual arma::mat Run() const = 0;
    
    virtual ~Routine() = default;
    
protected:
    std::unique_ptr<Gradient> gradient = nullptr;
};

class SimpleRoutine : public Routine {
public:
    SimpleRoutine(std::unique_ptr<Gradient>& grad) : gradient(std::move(grad)) {}
    
    arma::mat Run() const override {
        arma::mat grad = gradient->Eval(STARTING_POINT);
        arma::mat x = STARTING_POINT - STEP_SIZE * grad;
        while (arma::norm(grad, 2) > 0.00000001) {
            grad = gradient->Eval(x);
            x = x - STEP_SIZE * grad;
            std::cout << x << std::endl << std::endl;
        }
        return x;
    }

private:
    std::unique_ptr<Gradient> gradient = nullptr;
};


#endif /* routine_h */
