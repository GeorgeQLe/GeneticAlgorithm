/*  Copyright 2017 George Le

*/
#ifndef CONVOLUTIONAL_NEURAL_NETWORK_HPP
#define CONVOLUTIONAL_NEURAL_NETWORK_HPP

#include <map>
#include <string>
#include <vector>

#include "ANN/ANN_neuron.hpp"

class ConvolutionalNeuralNetwork 
{
    // accessor functions
	unsigned int number_of_hidden_layers() const { return m_main_neural_network.size();  }
	unsigned int hidden_layer_size(int hidden_layer_location) const { return m_main_neural_network.at(hidden_layer_location).size(); }

	// mutator functions

	/*-------------------------------------------------------------------------
	This function adds a layer at either the input layer of the FF_ANN
	It accepts a vector of neurons for the input layer of the neural net
	--------------------------------------------------------------------------*/
	bool push_back(std::vector<InputLayerNeuron> layer);
	/*-------------------------------------------------------------------------
	This function adds a layer at either the output layer of the FF_ANN
	It accepts a vector of neurons for the output layer of the neural net
	--------------------------------------------------------------------------*/
	bool push_back(std::vector<OutputLayerNeuron> layer);
	/*-------------------------------------------------------------------
	This overloaded function adds a layer hidden layer of the FF_ANN
	It accepts a vector of neurons and the index of the hidden layer
	--------------------------------------------------------------------*/
	bool push_back(std::vector<HiddenLayerNeuron> layer, unsigned int hidden_layer_location);

	/*--------------------------------------------------------------------------------
	This function evaluates the neural network and returns the result generated by the
 	neuron in the FF_NN's output layer with the highest output value.
	---------------------------------------------------------------------------------*/
	std::string evaluate_neural_net();

	// debug function


private:
	// holds hidden layers of the artificial neural network
	std::map<unsigned int, std::vector<HiddenLayerNeuron>> m_main_neural_network;

	// holds the neurons of the input layer
	std::vector<InputLayerNeuron> m_input_layer;

	// holds the neurons of the output layer
	std::vector<OutputLayerNeuron> m_output_layer;
};

#endif