#include "root.h"


double sigmoid(double x){ return 1 / (1 + exp(-x)); }

double dSigmoid(double x){ return sigmoid(x) * (1 - sigmoid(x)); }

void print_double_list(list<double> lst)
{
    list<double>::iterator it = lst.begin();
    cout<<"[";
    for (;it!=lst.end();)
    {
        cout<<*it;

        it++;
        if(it!=lst.end())
        {
            cout<<", ";
        }
    }
    cout<<"]\n";
}