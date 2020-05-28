#include "Neuron.h"

int main()
{
	Neuron* simone = new Neuron;
	simone->PrintId();
	delete(simone);//No memory leak
	std::cout<<"~~All clear~~"<<std::endl;
	return 0;
}
