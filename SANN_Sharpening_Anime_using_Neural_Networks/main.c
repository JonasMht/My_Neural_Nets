/*
Project: "Sharpening Anime with Neural Networks (SANN)"
Created by: Jonas Mehtali, 09/2020.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct int_listT {
         value;
    struct int_listT *prev;
    struct int_listT *next;
} int_list;


/*sigmoid function compresses all values in 0 to 1 range.
  It is also known as activation function.*/
double sigmoid(double x){
	return 1/(1+exp(-x));
}



int main()
{
    
    return 0;
}