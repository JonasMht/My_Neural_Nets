/*
Project: "Sharpening Anime with Neural Networks (SANN)"
Created by: Jonas Mehtali, 09/2020.
*/

/*
Neuron a = sigmoid(E(w*a)+bias)
Neuron connections(L-1 neurons)(weights, L-1 addrs)
*/


/*
Important note: create a neural network that corrects a given rectangle and patch multiple of them together to work on larger images.
*/

#include "network.h"


int main()
{
	clock_t start = clock();

	// Image testing part
	string filePath = "pic.ppm";
	fstream file;

	file.open(filePath, fstream::out);
	uint w = 500, h = 100;
	file << "P3" << endl;
	file << w << " " << h << endl;
	file << "255" << endl;


	//TrainingData trainingData("trainingSamples");

	vector<uint> topology;
	topology.push_back(2);
	topology.push_back(5);
	topology.push_back(5);
	topology.push_back(1);
	//trainingData.getTopology(topology);
	Net myNet(topology);

	vector<double> inputVals, targetVals, resultVals;
	int trainingPass = 0;

	while (trainingPass<50000)
	{
		++trainingPass;
		cout << endl << "Pass " <<trainingPass;
		inputVals.clear();
		targetVals.clear();
		uint a, b, c;
		a = (rand()/(double)RAND_MAX) > .5;
		b = (rand()/(double)RAND_MAX) > .5;
		c = (!a && b) || (a && !b);

		inputVals.push_back(a);
		inputVals.push_back(b);
		targetVals.push_back(a);

		// Get new imput data and feed it forward
		/*if (trainingData.getNextInputs(inputVals) != topology[0])
		{
			break;
		}*/
		showVectorVals(": Inputs:", inputVals);
		myNet.feedForward(inputVals);

		// Collect the net's actual results
		myNet.getResults(resultVals);
		showVectorVals("Outputs:", resultVals);
		
		// training the net what the outputs should have been
		/*trainingData.getTargetOutputs(targetVals);*/
		showVectorVals("Targets:", targetVals);
		assert(targetVals.size() == topology.back());

		myNet.backProp(targetVals);

		// report how wzll the training is working, averaged over recent error
		cout << "Net recent average error: "
			<< myNet.getRecentAverageError() << endl;

		uint grad = (uint) 255-255*myNet.getRecentAverageError();
		file << grad << " " << grad << " " << grad <<endl;

	}

	file.close();

	cout << endl << "Done\n";

	/*
	list<uint> layer_format; // {5,16,16,5} each element represents a layer and the value the amount of neurons
	layer_format.push_back(2);
	layer_format.push_back(16);
	layer_format.push_back(16);
	layer_format.push_back(2);
	NetworkClass nn(layer_format);
	nn.get_info();

	list<double> input;
	input.push_back(0.5);
	input.push_back(0.5);

	print_double_list(input);
	list<double> out = nn.test(input);
	print_double_list(out);
	cout<<"Cost of nn : "<< nn.cost(out, input) <<"\n";


	//save nn
	nn.save_nn("saves/save1.txt");
	//load nn
	nn.load_nn("saves/save1.txt");
	//nn.save_nn("save1.txt");
	nn.get_info();
	*/

	clock_t end = clock();
	cout<<"\nFinished execution, it took "<<(float)(end-start)/(CLOCKS_PER_SEC)<<" sec.\n";
	return 0;
}


	/*
	list_of_lists *list = init_double_list_of_lists(20,100,19.999);
	cout<<"list of "<<list_of_lists_len(list)<<" lists\n";
	//print_list_of_double_list(list);
	free_list_of_lists(list);
	*/

// ref
/*
for(auto i=entities.begin();i!=entities.end();)
		{
			Entity *e = *i;

			e->update();
			e->anim.update();

			if (e->life==false) {i=entities.erase(i); delete e;}
			else i++;
		}
*/