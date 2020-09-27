#ifndef ROOT_H
#define ROOT_H

#include <iostream>
#include <math.h>
#include <time.h>
#include <list>

using namespace std;

typedef unsigned int uint;


/*sigmoid function compresses all values in 0 to 1 range.
  It is also known as activation function.*/
double sigmoid(double x);
// Derivative of activation function
double dSigmoid(double x);

void print_double_list(list<double> lst);

#endif