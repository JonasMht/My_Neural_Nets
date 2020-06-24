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
  cout<<"ID : ["<<this->id[0]<<','<<this->id[1]<<','<<this->id[2]<<"]\n";
}

void Neuron::changeId(int x, int y, int z)
{
  this->id[0] = x;
  this->id[1] = y;
  this->id[2] = z;
}