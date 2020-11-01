#include "root.h"


uint rand_uint(uint n)
{
	if (n==0) {return 0;}
	else {return rand() % n;}
}

/**
 * \brief Random double between a and b.
 */
double rand_double(double a, double b)
{
	double diff = (b-a);
	return (rand()/(double)RAND_MAX)*diff + a;
}


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


void showVectorVals(string label, vector<double> &v)
{
	cout << label << " ";
	for (uint i = 0; i < v.size(); ++i)
	{
		cout << v[i]<< " ";
	}
	cout << endl;
}