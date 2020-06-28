#ifndef NEURON_H
#define NEURON_H

#include "Source.h"

class Construct // 3D Neuron
{
private:
    /*Variables*/
    list<strata *> stratas;

public:
    /*Constructor Destructor*/
    Construct();
    virtual ~Construct();

    /*Functions*/
    void InitStratas(int numInNeu, int numOutNeu, int depth, int numNeuPerStra);
    void DeleteStratas();
    void Update();
};

#endif
