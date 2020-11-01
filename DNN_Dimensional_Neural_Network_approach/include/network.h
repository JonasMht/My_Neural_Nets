#ifndef NETWORK_H
#define NETWORK_H

#include "neuron.h"

typedef vector<Neuron> Layer;

class Net
{
private:
	vector<Layer> layers; // layers[layerNum][neuronNum]
	/**
	 * \brief Direct error after a feed-forward.
	 */
	double error;
	/**
	 * \brief Sum of errors of each feed forward.
	 */
	double error_sum;
	/**
	 * \brief Number of feed-forwards.
	 */
	uint num_feedForwards;

public:

	Net(const vector<uint> &topology); // constructor
	
	Net(const Net *original); // copy constructor

	/**
	 * \brief Change a random parameter by a given value (change) in the range in [0,1].
	 */
	void mutate(double change);

	void feedForward(const vector<double> &inputVals, const vector<double> &targetVals); // (&) pass the reference

	double getAveragedError();

	/**
	 * \brief Resets error, error_sum and num_feedForward.
	 */
	void resetError();

	/**
	 * \brief Return a copy of the Layers.
	 */
	vector<Layer> getLayers() const;
	/**
	 * \brief Return the output after a feed-forward.
	 */
	vector<double> getOutput();


	//void backProp(const vector<double> &targetVals); // Net learning part
	//void getResults(vector<double> &resultVals) const; // const correctness, cannot be called by a non const function of the class
	//double getRecentAverageError() const; // get average over a given number of trainings
	


};


/*
class NetworkClass
{
private:

	list<uint> layer_format; // each element represents a layer and the value of each elements represent the amout of neurons

	list<list<double>> m_activ_layer; // a neuron is a node that holds a real number
	list<list<double>> m_bias_layers; // each neuron has its won bias used in the sigmoid function when forward feeding to the given layer
	list<list<double>> interlayer_weights; // between each layer there are as much weights as the dot product of both layer's neurons
	// weights for a given layer: each neuron from the second layer, dot product the neurons of the first layer.
	

	//averaged change of each parameter to affect at the end of a training session with training batches (mini)
	list<list<double>> m_bias_layers_change; // average change to the biases
	list<list<double>> interlayer_weights_change; // average change to the weights

	double learning_rate = 0.001;

public:
	NetworkClass(list<uint> layer_format, double learning_rate = 0.001); // constructor
	~NetworkClass(); // destructor

	void get_info();

	double error(double computed_output, double desired_output); // the error function defines the error between the input and desired output.
	double cost(list<double> computed_output, list<double> desired_output); // loss of one training sample using error finction
	double dCost_bias(double computed_output, double desired_output);
	double dCost_weight(double dC_dZ, double former_neurom_a);

	void feed_forward(list<double> &L0, list<double> &L1, list<double> &W_L0_L1, list<double> &L1_bias);
	list<double> test(list<double> input); // run neural network for a given input and return the output.
	void backprop(list<double> desired_output); // backprop the nn for an awaited result using the cost function changing the weight.
	void traim_om_batch(list<list<double>> training_input, list<list<double>> desired_output); // train the nn on a mini batch using backprop.

	// Save management 
	// File format:
	// lines about weight parameters
	// lines about the bias parameters,

	void load_nn(string file_path);
	void save_nn(string file_path);

};
*/

#endif