#include "neuron.h"

double Neuron::eta = 0.15; // overall net learning rate, [0.0..1.0]
double Neuron::alpha = 0.5; // momentum, multiplier of the last deltaWeight [0.0..n]

Neuron::Neuron(uint numOutputs, uint index)
{
	for (uint c = 0; c < numOutputs; ++c)
	{
		Connection conn{0.0, 0.0};
		conn.weight = (rand()/(double)RAND_MAX); // could be random
		this->m_outputWeights.push_back(conn);
	}

	this->m_index = index;
	
}

void Neuron::setOutputVal(double val) { this->m_outputVal = val; }

double Neuron::getOutputVal() const { return this->m_outputVal; }

double Neuron::transferFunction(double x)
{
	return sigmoid(x);
}

double Neuron::transferFunctionDerivative(double x)
{
	return dSigmoid(x);
}

double Neuron::sumDOW(const vector<Neuron> &nextLayer) const
{
	double sum = 0.0;

	// Sum our contributions of the errors at the nodes we feed

	for (uint n = 0; n < (nextLayer.size() - 1); ++n)
	{
		sum += this->m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}


void Neuron::feedForward(vector<Neuron> &prevLayer)
{
	double sum = 0.0;

	// Sum the previous layer's outputs (which are our inputs)
	// Include the bias node from the previous layer
	
	for (uint n = 0; n < prevLayer.size(); ++n)
	{
		sum += prevLayer[n].getOutputVal() * 
			prevLayer[n].m_outputWeights[m_index].weight;
	}

	this->m_outputVal = this->transferFunction(sum);
}

void Neuron::calcOutputGradients(double targetVal)
{
	double delta = targetVal - m_outputVal;
	this->m_gradient = delta * this->transferFunctionDerivative(this->m_outputVal);
}

void Neuron::calcHiddenGradients(const vector<Neuron> &nextLayer)
{
	double dow = sumDOW(nextLayer); // D of the weights of the next layer
	this->m_gradient = dow * this->transferFunctionDerivative(this->m_outputVal);
}

void Neuron::updateInputWeights(vector<Neuron> &prevLayer)
{
	// The weights to be updated are in the Connection container
	// in the neurons in the preceding layer

	for (uint n = 0; n < (prevLayer.size() - 1); ++n)
	{
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[this->m_index].deltaWeight; // the weight from it to us

		double newDeltaWeight = 
			// Individual inout, magnified by the gradient and training rate:
			this->eta
			* neuron.getOutputVal()
			* this->m_gradient;
			// Alpha add momentum = a fraction of the previous delta weight
			+ this->alpha
			* oldDeltaWeight;
			
		neuron.m_outputWeights[this->m_index].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[this->m_index].weight += newDeltaWeight;
	}
}