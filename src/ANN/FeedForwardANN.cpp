/*  Copyright 2017 George Le

Implementation of functions belonging to the FF_ANN and Neuron class

*/
#include <cmath> // exp()

#include "ANN/FeedForwardANN.hpp"

bool FF_ANN::push_back(std::vector<InputLayerNeuron> layer)
{
	if (layer.size() == 0)
	{
		// if there is nothing in the layer then
		// don't put the layer in the neural net
		// ERROR
		return false;
	}
	else
	{
		m_input_layer = layer;
	}

	return true;
}

bool FF_ANN::push_back(std::vector<OutputLayerNeuron> layer)
{
	if (layer.size() == 0)
	{
		// if there is nothing in the layer then
		// don't put the layer in the neural net
		// ERROR
		return false;
	}
	else
	{
		m_output_layer = layer;
	}

	return true;
}

bool FF_ANN::push_back(std::vector<HiddenLayerNeuron> layer, unsigned int hidden_layer_location)
{
	if (layer.size() == 0)
	{
		// if there is nothing in the layer then
		// don't put the layer in the neural net
		// ERROR
		return false;
	}
	else
	{
		// create the space and insert the layer into the neural net at the
		// hidden_layer_location position
		m_main_neural_network.emplace(hidden_layer_location, layer);
	}
	return true;
}

std::string FF_ANN::evaluate_neural_net()
{
	std::string temp;
	double value = 0.0;
	int index = 0, max_index = 0;

	

	return std::string();
}

