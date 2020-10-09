#ifndef NEURON_H
#define NEURON_H

#include "root.h"

struct Connection
{
	double weight;
	double deltaWeight;
};


class Neuron// forward reference to Neuron (not implemented yet)
{
public:
	Neuron(uint numOutputs, uint index);
	void setOutputVal(double val);
	double getOutputVal() const; // const does not modify the inner structure of the class
	void feedForward(vector<Neuron> &prevLayer);
private:
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	double m_outputVal;
	uint m_index;
	vector<Connection> m_outputWeights;
};

#endif