#include "Neuron.h"

int main()
{

	const int WIDTH = 10, HEIGHT = 10; //Dimension of the matrix
	//get time at the start of execution
	clock_t clockStart = clock();

	bool running = true;
	//Main program loop
	while (running)
	{
		string choice; //Input string
		cout << "\nChoices:\n\t- (q/0) : Quit\n\nAnswer:\t";
		cin >> choice;
		cout << '\n';
		
		if (choice.compare("1")==0)
		{
			// Create a blank neural net and save it
			ofstream outFile;
			outFile.open ("example.x", ios::out | ios::trunc);

			list<bool> message;
			message = IntTobList(1);
			printBoolList(message);
			cout <<" = "<< bListToInt(message) << "\n";

			string outString = "Something interesting\n";
			outString.append("Noon");
			outFile << outString;

			outFile.close();
		}
		else if (choice.compare("2")==0)
		{
			//test things
			list<Neuron*> nList;

			//Creation loop
			for (int i=0; i<100; i++)
			{
				Neuron *simone = new Neuron;
				simone->changeId(i,0,0);
				
				nList.push_front(simone);
			}
			
			//Deletion loop
			for (list<Neuron*>::iterator it = nList.begin(); it != nList.end(); ++it)
			{
				Neuron *e = *it;
				e->PrintId();

				delete(e);//No memory leak
			}
		}
		else if (choice.compare("q")==0 || choice.compare("0")==0)
		{
			running = false;
			cout << "Quitting\n";
		}
		else
		{
			cout << "This choice is incorrect (" << choice <<").\n";
		}
	}
	

	//get time at the end of execution
	clock_t clockEnd = clock();
	//get difference in time between the start and end of execution
	double time_spent = (double)(clockEnd - clockStart) / CLOCKS_PER_SEC;

	cout<<"-- Correct execution --\n";
	cout<<"-- Total runtime: "<<time_spent<<" seconds --\n";

	return 0;
}
