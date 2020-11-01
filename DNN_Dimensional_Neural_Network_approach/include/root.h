/**
 * \file root.h
 * \brief Déclaration.
 */

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
#include <stdlib.h>
#include <bits/stdc++.h> // sort function for vectors

using namespace std;

/**
 * \brief Definition of an unsigned int type.
 */
typedef unsigned int uint;

/**
 * \brief Random unisgned integer between 0 and n-1.
 */
uint rand_uint(uint n);

/**
 * \brief Random double between a and b.
 */
double rand_double(double a, double b);

/*sigmoid function compresses all values in 0 to 1 range.
  It is also known as activation function.*/
double sigmoid(double x);
// Derivative of activation function
double dSigmoid(double x);

void print_double_list(list<double> lst);

void showVectorVals(string label, vector<double> &v);

#endif