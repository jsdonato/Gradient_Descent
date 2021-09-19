#ifndef gradient_h
#define gradient_h
#include <armadillo>

class Gradient {
public:
    virtual arma::mat eval(arma::mat x) const = 0;
    
    virtual ~Gradient() = default;
};

//Derived class used to compute \nabla F(x) where F(x)=|Ax-b|_2^2
class LinSysGradient : public Gradient {
public:
    LinSysGradient(arma::mat A_, arma::mat b_) : A(A_), b(b_) {}
    
    arma::mat eval(arma::mat x) const override {
        return 2 * A.t() * (A * x - b);
    }
    
private:
    arma::mat A;
    arma::mat b;
};


#endif /* gradient_h */
