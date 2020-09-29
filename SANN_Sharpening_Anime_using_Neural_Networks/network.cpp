#include "network.h"

NetworkClass::NetworkClass(list<uint> layer_format, double learning_rate)
{
    this->learning_rate = learning_rate;
    int former_layer_n = 0;
    for(auto i=layer_format.begin();i!=layer_format.end();i++)
    {
        uint n = *i;
        /* add neurons to layer */
        list<double> layer_activations(n ,0.0); // add a neurons of activation 0
        this->n_activ_layer.push_back(layer_activations);
        

        /* add weights between layers */
        if (former_layer_n != 0) // if it isn't the first layer
        {
            list<double> between_layers_weights(n*former_layer_n, 0.0); // initiate weights at 0 // could init at random (tests needed)
            this->interlayer_weights.push_back(between_layers_weights);
            list<double> layer_biases(n ,0.0);
            this->n_bias_layers.push_back(layer_biases);
        }
        former_layer_n = n;
    }
}

NetworkClass::~NetworkClass()
{

}

void NetworkClass::get_info()
{
    cout <<"This NN contains "<<this->n_activ_layer.size()<<" layers\n";
    cout <<"Has "<<this->interlayer_weights.size()<<" weight lists\n";
}

double NetworkClass::error(double computed_output, double desired_output)
{
    double e = (computed_output - desired_output);
    return e*e;
}

/* derivatives */
double NetworkClass::dCost_bias(double computed_output, double desired_output)
{
    double dC_dO = computed_output-desired_output;
    double dO_dZ = desired_output * (1 - desired_output);
    double dC_dZ = dC_dO * dO_dZ;
    return dC_dZ;
}

double NetworkClass::dCost_weight(double dC_dZ, double former_neuron_output)
{
    double dC_dW = dC_dZ * former_neuron_output;
}



double NetworkClass::cost(list<double> computed_output, list<double> desired_output)
{
    double c = 0;
    if (computed_output.size() == desired_output.size())
    {
        list<double>::iterator c_out = computed_output.begin();
        list<double>::iterator d_out = desired_output.begin();
        for(;c_out!=computed_output.end();c_out++, d_out++)
        {
            c += this->error(*c_out, *d_out);
        }
        c = c/(computed_output.size());
    }

    return c;
}

void NetworkClass::feed_forward(list<double> &L0, list<double> &L1, list<double> &W_L0_L1, list<double> &L1_bias)
{
    double z = 0.0;
    list<double>::iterator N1 = L1.begin();
    list<double>::iterator B1 = L1_bias.begin();
    list<double>::iterator W_N0_N1 = W_L0_L1.begin();
    for(;N1!=L1.end();N1++, B1++)
    {
        list<double>::iterator N0 = L0.begin();
        for(;N0!=L0.end();N0++)
        {
            z += (*W_N0_N1) * (*N0);
            W_N0_N1++;
        }
        z += *B1;
        (*N1) = sigmoid(z);
        cout<<z<<" bias :"<<*B1<<", activation : "<<sigmoid(z)<<"\n";
        z = 0.0;
    }
}

list<double> NetworkClass::test(list<double> input)
{
    if (input.size() == (*this->n_activ_layer.begin()).size())
    {
        (*this->n_activ_layer.begin()) = input; // set in layer to the input if the input has the same format
    }
    list<list<double>>::iterator L0 = this->n_activ_layer.begin();
    list<list<double>>::iterator L1 = this->n_activ_layer.begin();
    list<list<double>>::iterator B1 = this->n_bias_layers.begin();
    L1++;
    list<list<double>>::iterator W_L0_L1 = interlayer_weights.begin();
    
    for(;L1!=this->n_activ_layer.end();L0++,L1++,W_L0_L1++,B1++)
    {
        this->feed_forward(*L0, *L1, *W_L0_L1, *B1);
    }
    return this->n_activ_layer.back(); // return out layer
}

void NetworkClass::backprop(list<double> desired_output)
{
    if (this->n_bias_layers_change.empty()) // no parameter change registered
    {
        list<list<double>>::iterator L0 = this->n_activ_layer.end();
        L0--;
        list<list<double>>::iterator L1 = this->n_activ_layer.end();
        list<list<double>>::iterator W_L0_L1 = interlayer_weights.end();

        list<list<double>>::iterator B1_change = this->n_bias_layers_change.end();
        list<list<double>>::iterator W_L0_L1_change = this->interlayer_weights_change.end();


        for(;L0!=this->n_activ_layer.begin(); L0--, L1--, W_L0_L1--, W_L0_L1_change-- ,B1_change--)
        {
            list<double>::iterator N1 = L1->begin();
            list<double>::iterator W_N0_N1 = W_L0_L1->begin();
            for(;N1!=L1->end();N1++)
            {
                list<double>::iterator N0 = L0->begin();
                for(;N0!=L0->end(); N0++)
                {
                    double dC_dW = dCost_bias()
                    B1_change->push_back();
                    W_L0_L1_change->push_back();
                    W_N0_N1++;
                }
            }
        }
    }
    
    
}

void NetworkClass::train_on_batch(list<list<double>> training_input, list<list<double>> desired_output)
{

}