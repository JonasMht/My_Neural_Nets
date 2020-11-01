/**
 * \file main.c
 * \brief Main file.
 */

/*
Project: "Sharpening Anime with Neural Networks (SANN)"
Created by: Jonas Mehtali, 09/2020.
*/

/*
Important note: create a neural network that corrects a given rectangle and patch multiple of them together to work on larger images.
*/

#include "network.h"

typedef struct {Net *n; double rank=0;} netRanking;

// comparison by rank.
bool compare_rank (const netRanking& first, const netRanking& second)
{
	return first.rank < second.rank;
}


void test_and_rank(vector<netRanking> &Nets)
{
	for(uint neuronRank = 0 ;neuronRank<Nets.size();++neuronRank)
	{
		for (int j=0; j<100; ++j)
		{
			bool b1 =rand() % 2;
			//bool b2 =rand() % 2;
			vector<double> inputVals;
			inputVals.push_back(b1);
			//inputVals.push_back(b2);
			vector<double> targetVals;
			targetVals.push_back(!b1);

			Nets[neuronRank].n->feedForward(inputVals, targetVals);
		}

		double error = Nets[neuronRank].n->getAveragedError();
		Nets[neuronRank].n->resetError();
		Nets[neuronRank].rank = error;
	}

	// sort the nets by rank
	sort(Nets.begin(), Nets.end(), compare_rank);

}


int main()
{
	clock_t start = clock();

	srand ( time(NULL) ); // rand seed


	// create topology
	vector<uint> topology;
	topology.push_back(1);
	topology.push_back(8);
	topology.push_back(8);
	topology.push_back(8);
	topology.push_back(1);

	vector<netRanking> Nets;
	for (int i=0; i<50; ++i)
	{
		netRanking ranking;
		ranking.n = new Net(topology);
		Nets.push_back(ranking);
	}

	
	
	
	for (int i=0; i<500; ++i)
	{
		for(uint neuronRank = 2 ;neuronRank<Nets.size();++neuronRank)
		{
			// Mutation by rank (previous error)
			Nets[neuronRank].n->mutate(rand_double(-Nets[neuronRank].rank*100.0, Nets[neuronRank].rank*100.0));
		}

		test_and_rank(Nets);

		if (i%100==0) cout <<" best rank :"<< Nets.begin()->rank<< endl;

		for(uint nr = 2 ;nr<Nets.size();++nr)
		{
			Nets[nr].n = new Net(Nets[nr%2].n);
			Nets[nr].rank = Nets[nr%2].rank;
		}

	}

	// test the best net
	for (int j=0; j<100; ++j)
	{
		bool b1 =rand() % 2;
		//bool b2 =rand() % 2;
		vector<double> inputVals;
		inputVals.push_back(b1);
		//inputVals.push_back(b2);
		vector<double> targetVals;
		targetVals.push_back(!b1);

		Nets[0].n->feedForward(inputVals, targetVals);
		cout <<" for " << b1 << " the output is "<< Nets[0].n->getOutput()[0] <<endl;
	}



	// free the allocated memory
	for(uint nr = 0 ;nr<Nets.size();++nr)
	{
      Net *n = Nets[nr].n;
	  cout << "Rank: " << Nets[nr].rank << endl;
	  delete n;
    }

	Nets.clear();

	

	clock_t end = clock();
	cout<<"\nFinished execution, it took "<<(float)(end-start)/(CLOCKS_PER_SEC)<<" sec.\n";
	return 0;
}

// Old tests
/*

double prototype_timer_sigmoid(uint time, uint threshold, double max_fact, double steepness){
	return max_fact / (1 + exp(steepness * ((double)time-threshold))); 
	}

double modif_sigmoid(double x, double bias, double steepness){ return 1 / (1 + exp( steepness * (-x+bias))); }

uint step_function(double x, double step) {return x >= step;}


// in the main function

// Test on a 1D neuron
	const uint EPOCHES = 20000;
	// have 3 neurons 1 input 1 output and one in between

	double n0=0, n1=0, n2=0;
	double t0=0, t1=0, gt=0; // gt is global timeer
	double bias0_1=(rand()/(double)RAND_MAX), bias1_2=(rand()/(double)RAND_MAX);
	double steepness0_1=(rand()/(double)RAND_MAX), steepness1_2=(rand()/(double)RAND_MAX);

	uint threshold = 6;
	double max_fact = 1.0;
	double steepness = 1;

	// System tested on not gate
	for (uint i = 0; i < EPOCHES; ++i)
	{
		double avrg_error = 0;
		uint training_runs = 1;
		for (uint k = 0; k<training_runs; ++k)
		{
			++gt;
			// sensory deprivation evolution
			uint b = (rand()/(double)RAND_MAX)>.5;
			double expected_out = !b;
			n0 += b; // add potential
			
			n1 += modif_sigmoid(n0,bias0_1,1);
			bias0_1 = bias0_1 * prototype_timer_sigmoid(gt-t0, threshold, max_fact, steepness); // Path reinforcelent
			++t0;

			
			n2 += modif_sigmoid(n1,bias1_2,1);
			bias1_2 = bias1_2 * prototype_timer_sigmoid(gt-t1, threshold, max_fact, steepness); // Path reinforcelent
			++t1;
			
			double error = (expected_out - n2) * (expected_out - n2); // error
			avrg_error += error;
			n0=0;
			n1=0;
			n2=0;
		}

		avrg_error = avrg_error/training_runs;
		

		uint depCycles = (int) (avrg_error); // calculated from the error
		for (uint j = 0; j < depCycles; ++j)
		{
			gt++;
		}
		if (depCycles > 0)
		{
		bias0_1 = bias0_1 * (prototype_timer_sigmoid(gt-t0, threshold, max_fact, steepness) + (rand()/(double)RAND_MAX)/100);
		bias1_2 = bias1_2 * (prototype_timer_sigmoid(gt-t1, threshold, max_fact, steepness) + (rand()/(double)RAND_MAX)/100);
		t0 = gt;
		t1 = gt;
		}
	}

	// test results (average)
	double avrg_err = 0;
	uint nb_tests = 200;
	for (uint i = 0; i < nb_tests; ++i)
	{
		uint b = (rand()/(double)RAND_MAX)>.5;
		double expected_out = !b;

		n0 = b;
		n1 = modif_sigmoid(n0,bias0_1,1);
		n2 = modif_sigmoid(n1, bias1_2,1);
		double error = (expected_out - n2) * (expected_out - n2);
		avrg_err += error;
		cout << "expected_out : " << expected_out << " Actual : " << n2 << endl;
	}
	avrg_err = avrg_err/nb_tests;

	cout << "testing results\n";
	cout << "Average error: " << avrg_err << endl;
	cout << "bias0_1 : " << bias0_1 << " bias1_2 : " << bias1_2 << endl;
	
	cout << prototype_timer_sigmoid(1, threshold, max_fact, steepness)<<endl;
*/