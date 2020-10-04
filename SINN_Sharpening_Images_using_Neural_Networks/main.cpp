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
  nn.save_nn("save1.txt");
  //load nn
  nn.load_nn("save1.txt");
  //nn.save_nn("save1.txt");
  nn.get_info();

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