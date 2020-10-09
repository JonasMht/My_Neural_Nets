#ifndef ROOT_H
#define ROOT_H

#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>
#include <list>
#include <vector>
#include <iomanip> // for lossless double to string conversion
#include <assert.h> // error checking library in c++


using namespace std;

typedef unsigned int uint;


/*sigmoid function compresses all values in 0 to 1 range.
  It is also known as activation function.*/
double sigmoid(double x);
// Derivative of activation function
double dSigmoid(double x);

void print_double_list(list<double> lst);

#endif