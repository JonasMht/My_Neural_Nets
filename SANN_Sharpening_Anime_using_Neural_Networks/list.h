#ifndef LIST_H
#define LIST_H

#include "root.h"

class NetworkClass
{
private:
    list<double> doubleList;
public:
    NetworkClass(); // constructor
    ~NetworkClass(); // destructor

    void get_info();

};



#endif