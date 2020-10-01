#ifndef LIST_H
#define LIST_H

#include "root.h"

class NetworkClass
{
private:

    list<list<double>> n_activ_layer; // a neuron is a node that holds a real number
    list<list<double>> n_bias_layers; // each neuron has its won bias used in the sigmoid function when forward feeding to the given layer
    list<list<double>> interlayer_weights; // between each layer there are as much weights as the dot product of both layer's neurons
    // weights for a given layer: each neuron from the second layer, dot product the neurons of the first layer.
    

    /*averaged change of each parameter to affect at the end of a training session with training batches (mini)*/
    list<list<double>> n_bias_layers_change; // average change to the biases
    list<list<double>> interlayer_weights_change; // average change to the weights

    double learning_rate = 0.001;

public:
    NetworkClass(list<uint> layer_format, double learning_rate = 0.001); // constructor
    ~NetworkClass(); // destructor

    void get_info();

    double error(double computed_output, double desired_output); // the error function defines the error between the input and desired output.
    double dCost_bias(double computed_output, double desired_output);
    double dCost_weight(double dC_dZ, double former_neuron_output);
    double cost(list<double> computed_output, list<double> desired_output); // loss of one training sample

    void feed_forward(list<double> &L0, list<double> &L1, list<double> &W_L0_L1, list<double> &L1_bias);
    list<double> test(list<double> input); // run neural network for a given input and return the output.
    void backprop(list<double> desired_output); // backprop the nn for an awaited result using the cost function changing the weight.
    void train_on_batch(list<list<double>> training_input, list<list<double>> desired_output); // train the nn on a mini batch using backprop.

    /* Save management */
    /*
    File format:
    lines about weight parameters
    lines about the bias parameters,
    */
   
    void load_nn(string file_path);
    void save_nn(string file_path);

};



#endif