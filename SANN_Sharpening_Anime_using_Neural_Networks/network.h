#ifndef LIST_H
#define LIST_H

#include "root.h"

class NetworkClass
{
private:
    list<list<double>> neuron_layers; // a neuron is a node that holds a real number
    list<list<double>> weights_L0_L1; // between each layer there are as much weights as the dot product of both layer's neurons
    // weights for a given layer: each neuron from the second layer, dot product the neurons of the first layer.
    list<double> bias_layers; // each layer has its won bias used in the sigmoid function when forward feeding to the given layer

    double learning_rate = 0.001;

public:
    NetworkClass(list<uint> layer_format, double learning_r = 0.001); // constructor
    ~NetworkClass(); // destructor

    void get_info();

    double cost(double computed_output, double desired_output); // the error function defines the error between the input and desired output.
    double dError(double computed_output, double desired_output); // dericative of the error function
    double meanSquaredError(list<double> computed_output, list<double> desired_output); // loss of one training sample
    double dSquaredErrorLoss(double computed_output, double desired_output, double former_n_a);
    double overallSquaredErrorLoss(list<list<double>> computed_output, list<list<double>> desired_output); // loss over multiple training samples

    void feed_forward(list<double> &first_layer, list<double> &second_layer, list<double> &weights, double bias);
    list<double> test(list<double> input); // run neural network for a given input and return the output.
    void backprop(); // backprop the nn for an awaited result using the cost function changing the weight.
    void train(); // train the nn on a mini batch using backprop.


};



#endif