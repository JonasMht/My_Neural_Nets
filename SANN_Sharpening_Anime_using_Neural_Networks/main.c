/*
Project: "Sharpening Anime with Neural Networks (SANN)"
Created by: Jonas Mehtali, 09/2020.
*/

/*
Neuron a = sigmoid(E(w*a)+bias)
Neuron connections(L-1 neurons)(weights, L-1 addrs)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "list.c"


/*sigmoid function compresses all values in 0 to 1 range.
  It is also known as activation function.*/
double sigmoid(double x){ return 1 / (1 + exp(-x)); }
// Derivative of activation function
double dSigmoid(double x) { return x * (1 - x); }

void 

int main()
{
  clock_t start = clock();
  list_of_lists *list = init_double_list_of_lists(20,100,19.999);
  printf("list of %d lists\n",list_of_lists_len(list));
  //print_list_of_double_list(list);
  free_list_of_lists(list);

  clock_t end = clock();
  printf("\nCorrect exe, took %f sec.\n", (float)(end-start)/(CLOCKS_PER_SEC));
  return 0;
}
