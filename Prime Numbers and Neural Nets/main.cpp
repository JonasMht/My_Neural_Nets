#include "Neuron.h"

int main()
{
	clock_t clockStart = clock();

	Neuron* simone = new Neuron;
	simone->PrintId();
	delete(simone);//No memory leak
	
	clock_t clockEnd = clock();
	double time_spent = (double)(clockEnd - clockStart) / CLOCKS_PER_SEC;
	std::cout<<"-- Correct execution --\n";
	std::cout<<"-- Runtime: "<<time_spent<<" seconds --\n";
	return 0;
}
