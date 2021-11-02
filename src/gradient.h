#ifndef gradient_h
#define gradient_h
#include <armadillo>

class Gradient {
public:
    Gradient() {} 

    virtual arma::cx_mat grad(const arma::cx_mat &x) const = 0;
     
    virtual double f(const arma::cx_mat& x) const = 0;

    virtual ~Gradient() = default;
};

class LinSysGradient : public Gradient {
public:
    LinSysGradient(arma::cx_mat A_, arma::cx_mat b_) : 
   	           A(A_), b(b_) {}
    
    arma::cx_mat grad(const arma::cx_mat& x) const override {
        return 2.0 * A.t() * (A * x - b);
    }

    double f(const arma::cx_mat& x) const override {
        return arma::norm((A * x - b).as_col(), 2);
    }
    
private:
    const arma::cx_mat A;
    const arma::cx_mat b;
};

class MatrixGradient : public Gradient {
public:
    MatrixGradient(arma::cx_mat A_, arma::cx_mat B_, arma::cx_mat C_, double error_weight_) :
                  A(A_), B(B_), C(C_), error_weight(error_weight_) {}
    
    arma::cx_mat grad(const arma::cx_mat& X) const override {
        arma::cx_mat result(X.n_rows, X.n_cols);
        const arma::cx_mat C_minus_AXB = C - A * X * B;
        
        for (uint64_t p = 0; p < X.n_rows; p++) {
            for (uint64_t q = 0; q < X.n_cols; q++) {
                
		std::complex<double> sum = error_weight * (1.0 - kroneckerDelta(p, q)) * X(p,q);
                for (uint64_t i = 0; i < C_minus_AXB.n_rows; i++) {
                    for (uint64_t j = 0; j < C_minus_AXB.n_cols; j++) {
                        sum += C_minus_AXB(i, j) * (-1.0 * A(i,p) * B(q, j));
                    }
                }
                result(p,q) = 2.0 * sum;
                
            }
        }
        return result;
    }

    double f(const arma::cx_mat& X) const override {
        return arma::norm((A * X * B - C).as_col(), 2) + error_weight * arma::norm((X - arma::diagmat(X)).as_col(), 2);
    }
    
    
private:
    const arma::cx_mat A;
    const arma::cx_mat B;
    const arma::cx_mat C;
    double error_weight;
    
    uint8_t kroneckerDelta(const size_t& i, const size_t& j) const { return (i == j) ? 1.0 : 0.0; }
};

#endif /* gradient_h */
