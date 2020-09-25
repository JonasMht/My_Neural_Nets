#ifndef LIST_H
#define LIST_H

#include "root.h"

class NetworkClass
{
private:
    list<list<double>> neuron_layers; // a neuron is a node that holds a real number
    list<list<double>> weight_layers; // between each layer there are as much weights as the dot product of both layer's neurons
    // weights for a given layer: each neuron from the second layer, dot product the neurons of the first layer.
    list<double> bias_layers; // each layer has its won bias used in the sigmoid function when forward feeding to the given layer

public:
    NetworkClass(list<uint> layer_format); // constructor
    ~NetworkClass(); // destructor

    void get_info();
    
    void feed_forward(list<double> &first_layer, list<double> &second_layer, list<double> &weights, double bias);
    list<double> test(list<double> input); // run neural network for a given input and return the output
    void backprop(); // backprop the nn for an awaited result using the cost function changing the weight
    void train(); // train the nn on a mini batch using backprop


};



#endif