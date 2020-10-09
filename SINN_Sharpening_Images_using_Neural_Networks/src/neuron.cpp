#include "neuron.h"

Neuron::Neuron(uint numOutputs, uint index)
{
	for (uint c = 0; c < numOutputs; ++c)
	{
		Connection conn;
		conn.weight = .5; // could be random
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