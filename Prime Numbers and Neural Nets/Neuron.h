#ifndef NEURON_H
#define NEURON_H

#include "Source.h"

class Neuron // 3D Neuron
{
private:
  /*Variables*/
  int id[3] = {0,0,0};
  Neuron* FriendPtr[6];

public:
  /*Constructor Destructor*/
  Neuron();
  virtual ~Neuron();
  /*Functions*/
  void Update();
  void PrintId();
  void changeId(int x, int y, int z);

};

#endif
