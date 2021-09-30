#ifndef constants_h
#define constants_h

#include <armadillo>

const arma::mat STARTING_POINT = {{-0.5, 0},
                                  {0, 0.5}};

const double ERROR_WEIGHT = 15;

const double STEP_SIZE = 0.00001;

#endif /* constants_h */
