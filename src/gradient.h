#ifndef gradient_h
#define gradient_h
#include <armadillo>

class Gradient {
public:
    Gradient() {}
    
    virtual arma::mat gradEval(const arma::mat &x) const = 0;
     
    virtual ~Gradient() = default;
};

class LinSysGradient : public Gradient {
public:
    LinSysGradient(arma::mat A_, arma::mat b_) : 
   	           A(A_), b(b_) {}
    
    arma::mat gradEval(const arma::mat& x) const override {
        return 2 * A.t() * (A * x - b);
    }
    
private:
    const arma::mat A;
    const arma::mat b;
};

class MatrixGradient : public Gradient {
public:
    MatrixGradient(arma::mat A_, arma::mat B_, arma::mat C_, double error_weight_) :
                  A(A_), B(B_), C(C_), error_weight(error_weight_) {}
    
    arma::mat gradEval(const arma::mat& X) const override {
        arma::mat result(X.n_rows, X.n_cols);
        const arma::mat C_minus_AXB = C - A * X * B;
        
        for (uint64_t p = 0; p < X.n_rows; p++) {
            for (uint64_t q = 0; q < X.n_cols; q++) {
                
                double sum = error_weight * (1 - kroneckerDelta(p, q)) * X(p,q);
                for (uint64_t i = 0; i < C_minus_AXB.n_rows; i++) {
                    for (uint64_t j = 0; j < C_minus_AXB.n_cols; j++) {
                        sum += C_minus_AXB(i, j) * (-1 * A(i,p) * B(q, j));
                    }
                }
                result(p,q) = 2 * sum;
                
            }
        }
        return result;
    }
    
    
private:
    const arma::mat A;
    const arma::mat B;
    const arma::mat C;
    double error_weight;
    
    uint8_t kroneckerDelta(const size_t& i, const size_t& j) const { return (i == j) ? 1 : 0; }
};

#endif /* gradient_h */
