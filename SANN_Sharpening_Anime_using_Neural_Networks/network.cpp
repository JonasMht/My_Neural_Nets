#include "network.h"

NetworkClass::NetworkClass(list<uint> layer_format, double learning_rate)
{
    this->layer_format = layer_format;
    this->learning_rate = learning_rate;
    int former_layer_n = 0;
    for(auto i=layer_format.begin();i!=layer_format.end();i++)
    {
        uint n = *i;
        /* add neurons to layer */
        list<double> layer_activations(n ,0.0); // add a neurons of activation 0
        list<double> layer_biases(n ,0.0); // add a neurons of activation 0
        this->n_activ_layer.push_back(layer_activations);
        this->n_bias_layers.push_back(layer_biases);

        /* add weights between layers */
        if (former_layer_n != 0) // if it isn't the first layer
        {
            list<double> between_layers_weights(n*former_layer_n, 0.0); // initiate weights at 0 // could init at random (tests needed)
            this->interlayer_weights.push_back(between_layers_weights);
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

void NetworkClass::feed_forward(list<double> &first_n_activ_layer, list<double> &second_n_activ_layer, list<double> &weights, list<double> &second_n_bias_layers)
{
    double z = 0.0;
    uint n_fl = first_n_activ_layer.size();
    uint n_sl = second_n_activ_layer.size();
    list<double>::iterator sl = second_n_activ_layer.begin();
    list<double>::iterator sl_b = second_n_bias_layers.begin();
    list<double>::iterator w_it = weights.begin();
    for(auto sl=second_n_activ_layer.begin();sl!=second_n_activ_layer.end();sl++, sl_b++)
    {
        for(auto fl=first_n_activ_layer.begin();fl!=first_n_activ_layer.end();fl++)
        {
            z += (*w_it) * (*fl);
            w_it++;
        }
        z += *sl_b;
        (*sl) = sigmoid(z);
        cout<<z<<" bias :"<<*sl_b<<", activation : "<<sigmoid(z)<<"\n";
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
    L1++; B1++;
    list<list<double>>::iterator W_L0_L1 = interlayer_weights.begin();
    
    for(;L1!=this->n_activ_layer.end();L0++,L1++,W_L0_L1++,B1++)
    {
        this->feed_forward(*L0, *L1, *W_L0_L1, *B1);
    }
    return this->n_activ_layer.back(); // return out layer
}

void NetworkClass::backprop(list<double> desired_output)
{
    if (this->n_bias_layers_change.empty())
    {
        int former_layer_n = 0;
        for(auto i=this->layer_format.begin();i!=this->layer_format.end();i++)
        {
            uint n = *i;
            /* biase change */
            list<double> layer_biases(n ,0.0);
            this->n_bias_layers_change.push_back(layer_biases);

            /* add weights between layers */
            if (former_layer_n != 0) // if it isn't the first layer
            {
                list<double> between_layers_weights(n*former_layer_n, 0.0); // initiate weights at 0 // could init at random (tests needed)
                this->interlayer_weights_change.push_back(between_layers_weights);
            }
            former_layer_n = n;
        }
    }
    
    list<list<double>>::iterator bl_change_it = this->n_bias_layers_change.begin();
    list<list<double>>::iterator wl_change_it = this->interlayer_weights_change.begin();
}

void NetworkClass::train_on_batch(list<list<double>> training_input, list<list<double>> desired_output)
{

}