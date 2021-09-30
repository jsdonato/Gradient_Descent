#ifndef input_h
#define input_h
#include <armadillo>

//MATRIX GRADIENT
const arma::mat A = {{3, 4},
                     {6, 8}};

const arma::mat B = {{7, 8},
                     {3, 5}};

const arma::mat C = {{2, 7},
                     {4, 14}};

//LINEAR SYSTEM GRADIENT
const arma::mat b = arma::colvec( {1, 2, 3} );;

#endif /* input_h */
