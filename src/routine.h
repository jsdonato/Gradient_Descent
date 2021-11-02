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
        arma::cx_mat g = gradient->grad(starting_point);
        arma::cx_mat x = starting_point - step_size * g;
        print(x);
	while (arma::norm(g, 2) > 0.00000001) {
            g = gradient->grad(x);
            x = x - step_size * g;
            print(x);
        }
        return x; 

    }

};

class ExperimentalRoutine : public Routine {
public:
    ExperimentalRoutine(std::shared_ptr<Gradient> gradient_, arma::cx_mat starting_point_, double initial_step_size_) : 
	          Routine(gradient_, starting_point_, initial_step_size_) {}

    

    arma::cx_mat Run() const override { 
	double temp_step_size = step_size;              
            arma::cx_mat g = gradient->grad(starting_point);
            arma::cx_mat old_x = starting_point;                
            arma::cx_mat new_x = starting_point - step_size * g;
            while (gradient->f(old_x) > gradient->f(new_x)) {                                                       
                temp_step_size *= 2;                         
                old_x = new_x;                               
                new_x = new_x - temp_step_size * g;
            }                                                                                                         
            g = gradient->grad(old_x);                            
            new_x = old_x - step_size * g;                        
            temp_step_size = step_size;                           
                                          
            print(old_x);                          
            while (arma::norm(g, 2) > 0.00000001) {              
                while (gradient->f(old_x) > gradient->f(new_x)) {                                                       
                    temp_step_size *= 2;                                                                                
                    old_x = new_x;                                                                                      
                    new_x = new_x - temp_step_size * g;                                                                 
                }                                                
                g = gradient->grad(old_x);                            
                new_x = old_x - step_size * g;                        
                temp_step_size = step_size;                           
                print(old_x);                                         
            }                                                         
            return old_x; 
    }

};


#endif /* routine_h */
