#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <iomanip> // for lossless double to string conversion


using namespace std;

#define unigned int uint

// Need to save the inputs and the wanted outputs
void saveVector2D(fstream &file, vector<vector<double>> &vector2D) // vector2D[][] = {inputs, wanted outputs}
{

	if (file.is_open())
	{
		for (uint line = 0; line < vector2D.size(); ++ line)
		{
			for (uint column = 0; column < vector2D[line].size(); ++column)
			{

				file << setprecision(10) << vector2D[line][column];
				if (column != (vector2D[line].size()-1))
					file << ',';
			}
			if (line != (vector2D.size()-1))
					file << '|';
		}
		file << ";\n";
	}
}

int main()
{
	string filePath = "trainingSamples";
	fstream file;
	file.open(filePath, fstream::out);

	for (uint i = 0; i < 4000; ++i)
	{
		uint a, b, c;
		a = (rand()/(double)RAND_MAX) > .5;
		b = (rand()/(double)RAND_MAX) > .5;
		c = (!a && b) || (a && !b);
		vector<double> inputs{a,b};
		vector<double> outputs{c};
		vector<vector<double>> vector2D{inputs, outputs};
		

		saveVector2D(file, vector2D);
	}

	file.close();


	cout <<"\nCorrect execution.\n";
	return 0;
}