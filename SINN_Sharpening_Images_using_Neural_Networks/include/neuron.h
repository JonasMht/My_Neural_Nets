#ifndef NEUROm_H
#define NEUROm_H

#include "trainingData.h"

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
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(const vector<Neuron> &nextLayer);
	void updateInputWeights(vector<Neuron> &prevLayer);

private:
	static double eta; // [0.0..1.0] overall net training rate
	static double alpha; // [0.0..n] multiplier of last weight change (momentum)
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	double sumDOW(const vector<Neuron> &nextLayer) const;
	double m_outputVal;
	uint m_index;
	vector<Connection> m_outputWeights;
	double m_gradient; //
};

#endif