#ifndef SOURCE_H
#define SOURCE_H

#include <iostream> //Library for command interface (cout cin)
#include <time.h>   //Library that allows the program to mesure time
#include <list>     //Library that implements lists
#include <fstream>  //Library that allows the program to write and read files
#include <string>   //Library that allows the use of strings (lists of characters)
#define PI 3.141592f

using namespace std; //Quit writing std:: in front of every damn library function

struct link
{
    void *neuronPtr = nullptr; //Pointer on another neuron
    float linkScalar = .0f;
};

struct neuron
{
    list<link *> links;
    float po; // Potential
};

struct strata
{
    list<neuron *> neurons;
};

struct construct
{
};

construct *newConstruct(int numInNeu, int numOutNeu, int depth, int numNeuPerStra);

void freeConstruct(construct *ct);

void printBoolList(list<bool> bList);

int bListToInt(list<bool> bList);

list<bool> IntTobList(int integer);

/*
File format ideas

#START
Score of this neuron arrangement for a given task
...
ID of neuron, Connections(neuron ID and bond strength)
...
#END
*/

/*
Binary messages:
[1,0,1]
Encode messages and orders in bytes

*/
#endif
