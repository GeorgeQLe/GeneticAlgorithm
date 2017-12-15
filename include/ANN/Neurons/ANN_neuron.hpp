/*  Copyright 2017 George Le

    This file contains the declarations for the base Neuron class and its
    derived InputLayerNeuron, HiddenLayerNeuron, and OutputLayerNeuron class.
*/
#ifndef ANN_NEURON_HPP
#define ANN_NEURON_HPP

#include <memory> // std::shared_ptr
#include <vector> // std::vector

/*----------------------------------------------------------------------------
|	A neuron is a base component of an artificial neural network. This class | 
|   contains a pure virtual function that all inheriting classes must 		 |
|   implement. 																 |
----------------------------------------------------------------------------*/
class Neuron
{
	public:
	Neuron() { }
	// this constructor should only be used for the input layer
	Neuron(double new_value) { m_neuron_value = new_value; }

	protected:
    /*---------------------------------------------------------------------------------------------
	    This neuron value is either the input layer's first input vectors or the output vector
	    of the hidden and output layer
	    for the output layer, this value will be evaluated on a range from values from 
        0 to 1 and be translated into the range's corresponding string value.
        for example if the ranges specified were:
        
            0 -> 0.5 is active low
            0.5 -> 1 is active high

        then if the neuron value is 0.6 then the output neuron will represent the value active high
        because it is in the range between 0.5 and 1 
	-----------------------------------------------------------------------------------------------*/
    double m_neuron_value;
};

#endif // ANN_NEURON_HPP