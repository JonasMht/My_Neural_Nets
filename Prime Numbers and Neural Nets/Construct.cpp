#include "Construct.h"

/*Constructor Destructor*/
Construct::Construct()
{
    cout << "Construct Created\n";
}

Construct::~Construct()
{
    this->DeleteStratas();
    cout << "Construct Destroyed\n";
}

void Construct::Update()
{
    for (list<strata *>::iterator it = this->stratas.begin(); it != this->stratas.end(); ++it)
    {
        strata *straPtr = *it;
        for(list<neuron*>::iterator it2 = straPtr->neurons.begin(); it2 != straPtr->neurons.end(); ++it2)
        {
            neuron *neuPtr = *it2;
            for(list<link*>::iterator it3 = neuPtr->links.begin(); it3 != neuPtr->links.end(); ++it3)
            {
                link *linkPtr = *it3;
                (linkPtr->neuronPtr)->po += 

            }
        }
    }
}

void Construct::InitStratas(int numInNeu, int numOutNeu, int depth, int numNeuPerStra)
{
    // Create stratas and neurons

    // Create in strata
    strata *inStra = new strata;
    for (int i = 0; i < numInNeu; i++)
    {
        neuron *neu = new neuron;
        (*inStra).neurons.push_front(neu);
    }
    this->stratas.push_front(inStra);

    // Create intermediary stratas
    for (int i = 0; i < (depth); i++)
    {
        strata *logicStra = new strata;
        for (int i = 0; i < numOutNeu; i++)
        {
            neuron *neu = new neuron;
            (*logicStra).neurons.push_front(neu);
        }
        this->stratas.push_front(logicStra);
    }

    // Create out strata
    strata *outStra = new strata;
    for (int i = 0; i < numOutNeu; i++)
    {
        neuron *neu = new neuron;
        (*outStra).neurons.push_front(neu);
    }
    this->stratas.push_front(outStra);
    //Link neurons between stratas
}

void Construct::DeleteStratas()
{
    for (list<strata *>::iterator itSt = this->stratas.begin(); itSt != this->stratas.end(); ++itSt)
    {
        strata *st = *itSt;
        for (list<neuron *>::iterator itOutNeu = (*st).neurons.begin(); itOutNeu != (*st).neurons.end(); ++itOutNeu)
        {
            neuron *neu = *itOutNeu;
            for (list<link *>::iterator itLnk = (*neu).links.begin(); itLnk != (*neu).links.end(); ++itLnk)
            {
                link *lnk = *itLnk;
                delete (lnk);
            }
            (*neu).links.empty();
            delete (neu);
        }
        (*st).neurons.empty();
        delete (st);
    }
}