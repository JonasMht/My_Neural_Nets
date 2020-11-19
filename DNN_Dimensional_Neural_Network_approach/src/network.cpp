#include "network.h"


Net::Net(const vector<uint> &topology)
{
	this->error = 0;
	this->error_sum = 0;
	this->num_feedForwards = 0;

	uint numLayers = topology.size();
	for (uint layerNum = 0; layerNum < numLayers; ++layerNum)
	{
		this->layers.push_back(Layer());
		uint numOutputs = layerNum == (topology.size() - 1) ? 0 : topology[layerNum + 1]; // find the number of neurons in the next layer (if it exists)

		// We have made a new Layer, now fill it with neurons,
		// and add a bias neuron to the layer as the last element;
		for (uint neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum)
		{
			this->layers.back().push_back(Neuron(numOutputs, neuronNum)); // New neuron created
		}

		// No more need for a bias neuron
		// Force the bias node's output value to 1.0. It's the last neuron created above
		//this->layers.back().back().setOutputVal(1.0);
	}
}

Net::Net(const Net *original)
{
	this->error = 0;
	this->error_sum = 0;
	this->num_feedForwards = 0;
	this->layers = original->getLayers();
}


void Net::mutate(double change)
{
	bool bMutation = rand_bool(); // Decides if the weight or bias is changed

	// Chose a random neuron
	uint layer = rand_uint(this->layers.size()-1); // minus the output layer
	uint neuron = rand_uint(this->layers[layer].size());

	if (bMutation)
	{
		uint num_outputWeights = this->layers[layer][neuron].outputWeights.size();
		uint outputWeight = rand_uint(num_outputWeights);
		this->layers[layer][neuron].outputWeights[outputWeight] += change;
	}
	else
	{
		this->layers[layer][neuron].add_to_bias(change);
	}

}


void Net::feedForward(const vector<double> &inputVals, const vector<double> &targetVals)
{
	++this->num_feedForwards;
	//assert(inputVals = layers[0].size() - 1); // c++ error check

	// Assign the inout values int o the input neuron
	for (uint i = 0; i < inputVals.size(); ++i)
	{
		this->layers[0][i].setOutputVal(inputVals[i]);
	}

	// Forward propagate
	for (uint layerNum = 1; layerNum < this->layers.size(); ++layerNum)
	{
		Layer &prevLayer = this->layers[layerNum - 1]; // by refference (works like a copy but is a reference to the original)
		for (uint n = 0; n < (this->layers[layerNum].size() - 1); ++n)
		{
			this->layers[layerNum][n].feedForward(prevLayer);
		}
	}

	// Get error

	Layer &outputLayer = this->layers.back();
	this->error = 0;
	for (uint n = 0; n < (outputLayer.size() - 1); ++n)
	{
		double delta = targetVals[n] - outputLayer[n].getOutputVal(); // difference between wanted output and actual output
		this->error += delta * delta;
	}
	this->error /= outputLayer.size() - 1; // get average error squared
	this->error = sqrt(this->error);	 // RMS

	this->error_sum += this->error;
}

double Net::getAveragedError()
{
	// note : error must be devised by max output value
	return this->error_sum / this->num_feedForwards;
}

void Net::resetError()
{
	this->error = 0;
	this->error_sum = 0;
	this->num_feedForwards = 0;
}

vector<Layer> Net::getLayers() const
{
	return this->layers;
}

vector<double> Net::getOutput()
{
	Layer &outputLayer = this->layers.back();
	vector<double> output;
	for (int i = 0; i<outputLayer.size(); ++i)
	{
		output.push_back(outputLayer[i].getOutputVal());
	}
	
	return output;
}


// Old archieved code

/*
void Net::backProp(const vector<double> &targetVals)
{

	// Calculate overall net error (RMS (Root Mean Square Error) of output neuron errors)
	Layer &outputLayer = this->layers.back();
	this->m_error = 0.0;
	for (uint n = 0; n < (outputLayer.size() - 1); ++n)
	{
		double delta = targetVals[n] - outputLayer[n].getOutputVal(); // difference between wanted output and actual output
		this->m_error += delta * delta;
	}
	this->m_error /= outputLayer.size() - 1; // get average error squared
	this->m_error = sqrt(this->m_error);	 // RMS

	// Implement a recent average mesurement: (how well the net did over all the sets until then)

	this->m_recentAverageError = (this->m_recentAverageError * this->m_recentAverageSmoothingFactor + this->m_error) / (this->m_recentAverageSmoothingFactor + 1.0);
	//this->m_recentAverageError = (this->m_recentAverageError * this->m_recentAverageSmoothingFactor + this->m_error) / (this->m_recentAverageSmoothingFactor + 1.0);

	// Calculate output layer gradients

	for (uint n = 0; n < (outputLayer.size() - 1); ++n)
	{
		outputLayer[n].calcOutputGradients(targetVals[n]);
	}

	// Calculate gradients on hidden layers

	for (uint layerNum = (this->layers.size() - 2); layerNum > 0; --layerNum) // Loop through the front layers
	{
		Layer &hiddenLayer = this->layers[layerNum];
		Layer &nextLayer = this->layers[layerNum + 1];

		for (uint n = 0; n < hiddenLayer.size(); ++n)
		{
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	// For all layers from outputs to first hidden layer,
	// update conenction weights

	for (uint layerNum = this->layers.size() - 1; layerNum > 0; --layerNum)
	{
		Layer &layer = this->layers[layerNum];
		Layer &prevLayer = this->layers[layerNum - 1];

		for (uint n = 0; n < (layer.size() - 1); ++n)
		{
			layer[n].updateInputWeights(prevLayer);
		}
	}
}

void Net::getResults(vector<double> &resultVals) const
{
	resultVals.clear();

	for (uint n = 0; n < (this->layers.back().size() - 1); ++n)
	{
		resultVals.push_back(this->layers.back()[n].getOutputVal());
	}
}

double Net::getRecentAverageError() const
{
	return this->m_recentAverageError;
}

*/


/*

NetworkClass::NetworkClass(list<uint> layer_format, double learning_rate)
{
	this->layer_format = layer_format;
	this->learning_rate = learning_rate;
	int former_layer_n = 0;
	for (auto i = layer_format.begin(); i != layer_format.end(); i++)
	{
		uint n = *i;
		// add neurons to layer 
		list<double> layer_activations(n, 0.0); // add a neurons of activation 0
		this->m_activ_layer.push_back(layer_activations);

		// add weights between layers 
		if (former_layer_n != 0) // if it isn't the first layer
		{
			list<double> betweelayers_weights(n * former_layer_n, 0.0); // initiate weights at 0 // could init at random (tests needed)
			this->interlayer_weights.push_back(betweelayers_weights);
			list<double> layer_biases(n, 0.0);
			this->m_bias_layers.push_back(layer_biases);
		}
		former_layer_n = n;
	}
}

NetworkClass::~NetworkClass()
{
}

void NetworkClass::get_info()
{
	cout << "This NN contains " << this->m_activ_layer.size() << " layers\n";
	cout << "Has " << this->interlayer_weights.size() << " weight lists\n";
}

double NetworkClass::error(double computed_output, double desired_output)
{
	double e = (computed_output - desired_output);
	return e * e;
}

double NetworkClass::cost(list<double> computed_output, list<double> desired_output)
{
	double c = 0;
	if (computed_output.size() == desired_output.size())
	{
		list<double>::iterator c_out = computed_output.begin();
		list<double>::iterator d_out = desired_output.begin();
		for (; c_out != computed_output.end(); c_out++, d_out++)
		{
			c += this->error(*c_out, *d_out);
		}
		c = c / (computed_output.size());
	}

	return c;
}

// derivatives 
double NetworkClass::dCost_bias(double computed_output, double desired_output)
{
	double dC_dA = 2 * (computed_output - desired_output);
	double dA_dZ = desired_output * (1 - desired_output); // derivative for the sigmoid function !
	double dC_dZ = dC_dA * dA_dZ;
	return dC_dZ;
}

double NetworkClass::dCost_weight(double dC_dZ, double former_neurom_a)
{
	double dC_dW = dC_dZ * former_neurom_a;
}

void NetworkClass::feed_forward(list<double> &L0, list<double> &L1, list<double> &W_L0_L1, list<double> &L1_bias)
{
	double z = 0.0;
	list<double>::iterator N1 = L1.begin();
	list<double>::iterator B1 = L1_bias.begin();
	list<double>::iterator W_N0_N1 = W_L0_L1.begin();
	for (; N1 != L1.end(); N1++, B1++)
	{
		list<double>::iterator N0 = L0.begin();
		for (; N0 != L0.end(); N0++)
		{
			z += (*W_N0_N1) * (*N0);
			W_N0_N1++;
		}
		z += *B1;
		(*N1) = sigmoid(z);
		z = 0.0;
	}
}

list<double> NetworkClass::test(list<double> input)
{
	if (input.size() == (*this->m_activ_layer.begin()).size())
	{
		(*this->m_activ_layer.begin()) = input; // set in layer to the input if the input has the same format
	}
	list<list<double>>::iterator L0 = this->m_activ_layer.begin();
	list<list<double>>::iterator L1 = this->m_activ_layer.begin();
	list<list<double>>::iterator B1 = this->m_bias_layers.begin();
	L1++;
	list<list<double>>::iterator W_L0_L1 = interlayer_weights.begin();

	for (; L1 != this->m_activ_layer.end(); L0++, L1++, W_L0_L1++, B1++)
	{
		this->feed_forward(*L0, *L1, *W_L0_L1, *B1);
	}
	return this->m_activ_layer.back(); // return out layer
}

void NetworkClass::backprop(list<double> desired_output)
{
	if (this->m_bias_layers_change.empty()) // no parameter change registered
	{
		list<list<double>>::iterator L0 = this->m_activ_layer.end();
		L0--;
		list<list<double>>::iterator L1 = this->m_activ_layer.end();
		list<list<double>>::iterator W_L0_L1 = this->interlayer_weights.end();

		list<list<double>>::iterator B1_change = this->m_bias_layers_change.end();
		list<list<double>>::iterator W_L0_L1_change = this->interlayer_weights_change.end();

		for (; L0 != this->m_activ_layer.begin(); L0--, L1--, W_L0_L1--, W_L0_L1_change--, B1_change--)
		{
			list<double>::iterator N1 = L1->begin();
			list<double>::iterator W_N0_N1 = W_L0_L1->begin();
			for (; N1 != L1->end(); N1++)
			{
				list<double>::iterator N0 = L0->begin();
				for (; N0 != L0->end(); N0++)
				{
					//double dC_dW = dCost_bias()
					//B1_change->push_back();
					//W_L0_L1_change->push_back();
					W_N0_N1++;
				}
			}
		}
	}
}

void NetworkClass::traim_om_batch(list<list<double>> training_input, list<list<double>> desired_output)
{
}

// Save management 
void NetworkClass::load_nn(string file_path)
{
	fstream file;

	file.open(file_path, fstream::in);
	if (file.is_open())
	{
		this->interlayer_weights.clear(); // remove fomer neuronal structure
		this->m_bias_layers.clear();
		this->m_activ_layer.clear();
		this->layer_format.clear();

		uint load_switch = 0;
		string line;

		list<double> arguments;
		while (getline(file, line))
		{
			string word = "";
			uint str_len = line.length();
			for (int it = 0; it < str_len; it++)
			{
				char c = line.at(it);
				if (c != ',' && c != ';')
				{
					word += c;
				}
				else
				{
					if (word.at(0) == '-')
					{
						cout << "Loading : " << word << "\n";
						load_switch++;
					}
					else if (word.at(0) != '#')
					{
						arguments.push_back(stod(word));

						if (c == ';')
						{
							switch (load_switch)
							{
							case 1:
							{
								list<double>::iterator arg_it = arguments.begin();
								for (; arg_it != arguments.end(); arg_it++)
									this->layer_format.push_back((int)(*arg_it));

								// initialize lists 
								list<uint>::iterator format_it = this->layer_format.begin();
								for (; format_it != this->layer_format.end(); format_it++)
								{
									uint n = *format_it;
									list<double> layer_activations(n, 0.0); // add n activations of 0
									this->m_activ_layer.push_back(layer_activations);
								}
							}
							break;
							case 2:
							{
								this->interlayer_weights.push_back(arguments);
							}
							break;
							case 3:
							{
								this->m_bias_layers.push_back(arguments);
							}
							break;

							default:
								break;
							}
							arguments.clear();
						}
					}

					word = "";
				}
			}
		}
		file.close();
	}
}
void NetworkClass::save_nn(string file_path)
{
	fstream file;

	file.open(file_path, fstream::out);
	if (file.is_open())
	{
		// - start of section, # comment (reader skips the line)
		file << "#START_Nm_SAVE;\n";
		file << "-START_FORMAT;\n";
		list<uint>::iterator NL = this->layer_format.begin();
		for (; NL != this->layer_format.end();)
		{
			file << to_string(*NL);
			NL++;
			if (NL != this->layer_format.end())
				file << ',';
			else
				file << ";\n";
		}
		file << "#END_FORMAT;\n";

		file << "-START_WEIGHTS;\n";
		list<list<double>>::iterator WL = this->interlayer_weights.begin();
		for (; WL != this->interlayer_weights.end(); WL++)
		{
			list<double>::iterator w = WL->begin();
			for (; w != WL->end();)
			{
				file << setprecision(10) << *w;
				w++;
				if (w != WL->end())
					file << ',';
				else
					file << ";\n";
			}
		}
		file << "#END_WEIGHTS;\n";
		file << "-START_BIASES;\n";
		list<list<double>>::iterator BL = this->m_bias_layers.begin();
		for (; BL != this->m_bias_layers.end(); BL++)
		{
			list<double>::iterator b = BL->begin();
			for (; b != BL->end();)
			{
				file << setprecision(10) << *b;
				b++;
				if (b != BL->end())
					file << ',';
				else
					file << ";\n";
			}
		}
		file << "#END_BIASES;\n";
		file << "#END_Nm_SAVE;\n";

		file.close();
	}
}

*/

