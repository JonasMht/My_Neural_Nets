#include "Neuron.h"

/*Constructor Destructor*/
Neuron::Neuron()
{
  for (int i=0; i<3;i++)
    this->id[i] = 0;
}

Neuron::~Neuron()
{

}

void Neuron::Update()
{

}

void Neuron::PrintId()
{
  std::cout<<this->id[0]<<this->id[1]<<this->id[2]<<std::endl;
}
