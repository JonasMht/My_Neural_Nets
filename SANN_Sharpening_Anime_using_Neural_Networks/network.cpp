#include "network.h"

NetworkClass::NetworkClass(list<unsigned int> layer_format)
{
    int former_layer_n = 0;
    for(auto i=layer_format.begin();i!=layer_format.end();i++)
    {
        unsigned int n = *i;
        /* add neurons to layer */
        list<double> single_layer(n ,0.0); // add e neurons of activation 0
        this->neuron_layers.push_back(single_layer);

        /* add weights between layers */
        if (former_layer_n != 0) // if it isn't the first layer
        {
            list<double> between_layers_weights(n*former_layer_n, 0.0); // initiate weights at 0 // could init at random (tests needed)
            this->weight_layers.push_back(between_layers_weights);
        }
        former_layer_n = n;
    }
}

NetworkClass::~NetworkClass()
{

}

void NetworkClass::get_info()
{
    cout <<"This NN contains "<<this->neuron_layers.size()<<" layers\n";
    cout <<"Has "<<this->weight_layers.size()<<" weight lists\n";
}

void feed_forward(list<double> &first_layer, list<double> &second_layer, list<double> &weights, double bias)
{
    double a = 0.0;
    unsigned int first_count;
    list<double>::iterator it = weights.begin();
    for(auto sl=second_layer.begin();sl!=second_layer.end();sl++)
    {
        for(auto fl=first_layer.begin();fl!=first_layer.end();fl++)
        {
            
        }
    }
}