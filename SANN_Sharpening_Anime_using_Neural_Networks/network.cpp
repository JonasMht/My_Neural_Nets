#include "network.h"

NetworkClass::NetworkClass(list<uint> layer_format, double learning_r)
{
    this->learning_rate = learning_r;
    int former_layer_n = 0;
    for(auto i=layer_format.begin();i!=layer_format.end();i++)
    {
        uint n = *i;
        /* add neurons to layer */
        list<double> single_layer(n ,0.0); // add e neurons of activation 0
        this->neuron_layers.push_back(single_layer);

        /* add bias to layer */
        bias_layers.push_back(0.0);

        /* add weights between layers */
        if (former_layer_n != 0) // if it isn't the first layer
        {
            list<double> between_layers_weights(n*former_layer_n, 0.0); // initiate weights at 0 // could init at random (tests needed)
            this->weights_L0_L1.push_back(between_layers_weights);
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
    cout <<"Has "<<this->weights_L0_L1.size()<<" weight lists\n";
}

double NetworkClass::cost(double computed_output, double desired_output)
{
    double e = (computed_output - desired_output);
    return e*e;
}

double dError(double computed_output, double desired_output)
{
    return 2*(computed_output - desired_output);
}

double NetworkClass::meanSquaredError(list<double> computed_output, list<double> desired_output)
{
    double cost = 0;
    if (computed_output.size() == desired_output.size())
    {
        list<double>::iterator c_out = computed_output.begin();
        list<double>::iterator d_out = desired_output.begin();
        for(;c_out!=computed_output.end();c_out++, d_out++)
        {
            cost += this->cost(*c_out, *d_out);
        }
        cost = cost/(computed_output.size());
    }

    return cost;
}

double NetworkClass::dSquaredErrorLoss(double computed_output, double desired_output, double former_n_a)
{
    double diff = desired_output - computed_output;
    double dErr = computed_output*(1-computed_output);
    double delta = diff * dErr;

    return delta * former_n_a;
}

void NetworkClass::feed_forward(list<double> &first_layer, list<double> &second_layer, list<double> &weights, double bias)
{
    double z = 0.0;
    uint n_fl = first_layer.size();
    uint n_sl = second_layer.size();
    list<double>::iterator w_it = weights.begin();
    for(auto sl=second_layer.begin();sl!=second_layer.end();sl++)
    {
        for(auto fl=first_layer.begin();fl!=first_layer.end();fl++)
        {
            z += (*w_it) * (*fl);
            w_it++;
        }
        z += bias;
        (*sl) = sigmoid(z);
        cout<<z<<" bias :"<<bias<<"activaiton"<<sigmoid(z)<<"\n";
        z = 0.0;
    }
}

list<double> NetworkClass::test(list<double> input)
{
    if (input.size() == (*this->neuron_layers.begin()).size())
    {
        (*this->neuron_layers.begin()) = input; // set in layer to the input if the input has the same format
    }
    list<list<double>>::iterator L0 = neuron_layers.begin();
    list<list<double>>::iterator L1 = neuron_layers.begin();
    L1++;
    list<list<double>>::iterator W_L0_L1 = weights_L0_L1.begin();
    list<double>::iterator B1 = bias_layers.begin();
    for(;L1!=neuron_layers.end();L0++,L1++,W_L0_L1++,B1++)
    {
        this->feed_forward(*L0, *L1, *W_L0_L1, *B1);
    }
    return this->neuron_layers.back(); // return out layer
}