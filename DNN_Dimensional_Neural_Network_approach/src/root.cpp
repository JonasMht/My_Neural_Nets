#include "root.h"

bool rand_bool()
{
	return (bool) rand() % 2;
}

uint rand_uint(uint n)
{
	if (n==0) {return 0;}
	else {return rand() % n;}
}

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

vector<uint> load_ppm(string file_path)
{
	vector<uint> image_vect;
	fstream file;

	file.open(file_path, fstream::in);

	/*
	if (file.is_open())
	{

		uint load_switch = 0;
		string line;

		list<double> arguments;
		while (getline(file, line))
		{
			string word = "";
			uint str_len = line.length();
			for (int it = 0; it < str_len; it++)
			{
				char c = line.at(it);
				if (c != ',' && c != ';')
				{
					word += c;
				}
				else
				{
					if (word.at(0) == '-')
					{
						cout << "Loading : " << word << "\n";
						load_switch++;
					}
					else if (word.at(0) != '#')
					{
						arguments.push_back(stod(word));

						if (c == ';')
						{
							switch (load_switch)
							{
							case 1:
							{
								list<double>::iterator arg_it = arguments.begin();
								for (; arg_it != arguments.end(); arg_it++)
									this->layer_format.push_back((int)(*arg_it));

								// initialize lists 
								list<uint>::iterator format_it = this->layer_format.begin();
								for (; format_it != this->layer_format.end(); format_it++)
								{
									uint n = *format_it;
									list<double> layer_activations(n, 0.0); // add n activations of 0
									this->m_activ_layer.push_back(layer_activations);
								}
							}
							break;
							case 2:
							{
								this->interlayer_weights.push_back(arguments);
							}
							break;
							case 3:
							{
								this->m_bias_layers.push_back(arguments);
							}
							break;

							default:
								break;
							}
							arguments.clear();
						}
					}

					word = "";
				}
			}
		}
		file.close();
	}
	*/
	return image_vect;
}



double rgb_to_unit(vector<uint> rgb_color)
{
	uint value = rgb_color[0] * 1000000 + rgb_color[1] * 1000 + rgb_color[2];
	return value / 1000000000.0;
}

vector<uint> unit_to_rgb(double unit)
{
	vector<uint> color;
	uint r, g, b;
	r = (uint)(unit*1000);
	unit = unit * 1000 - r;
	g = (uint)(unit*1000);
	unit = unit * 1000 - g;
	b = (uint)(unit*1000);

	color.push_back(r);
	color.push_back(g);
	color.push_back(b);

	return color;
}