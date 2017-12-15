/*

*/

#ifndef ANN_LAYERS_HPP
#define ANN_LAYERS_HPP

#include <map>

#include "ANN/Activation_Functions/activation_functions.hpp"
#include "ANN_neuron.hpp"

/*-------------------------------------------------------------------------------  
|	Neurons in the hidden layer work as filters for the neural network being	|
|	able to take in all of the input vectors of the previous layer (could be	|
|	the input layer or another layer in the hidden layer) and output whether	|
|	the inputs compared to a bias are significant enough for the neural net		|
|	to factor into its decision. Neurons' outputs are simply a number, in this	|
|	implementation, a double precision floating point number.					|
-------------------------------------------------------------------------------*/
class HiddenLayerNeuron : protected Neuron
{
public:
	HiddenLayerNeuron(std::vector<double> input_vectors, std::vector<double> input_weights, double bias) 
			: m_input_vectors(input_vectors), m_input_weight(input_weights), m_bias(bias), m_summation(0),
			summation_complete(false) { }

	// accessor functions for use by the neural network for backpropogation and gradient descent
	double get_input_vector(int index) { return m_input_vectors.at(index); }
	double get_input_weight(int index) { return m_input_weight.at(index); }
	double get_bias() { return m_bias; }

	void calculate_output(Activation_function<Sigmoid> function_to_be_used);

private:
	/*------------------------------------------
		Calculates u = (summation of wi * xi + bias)
	-------------------------------------------*/
	double summation_weight_input_vector();

	// a vector of all input vectors from either the inputs
	// or the outputs of the neurons of the previous layers
	std::vector<double> m_input_vectors;
	// should not be used if Neuron is in input layer
	std::vector<double> m_input_weight;
	// bias value of the neuron (optional-use with perceptron), which has values less
	// than the bias are ignored by the neural network
	double m_bias;

	// summation calculated in summation_weight_input_vector()
	double m_summation;

	// does not allow transfer functions to work until summation
	// has been calculated
	// reset after use in transfer functions
	bool summation_complete;

	// the default constructor of the hidden layer neuron is private to prevent the use of hidden layer neurons without
	// passing through the required parameters to create the neuron
	HiddenLayerNeuron() { }
};

/*-----------------------------------------------------------------------------------------
|    The InputLayerNeuron takes in values that are contextually available to the neural   |	
|    network to use in solving the problem posed to the neural network. These values must |
|    be translated in some form to doubles if they are not 	 							  |
------------------------------------------------------------------------------------------*/
class InputLayerNeuron : protected Neuron
{
public:
	InputLayerNeuron::InputLayerNeuron(double value) : Neuron(value) { }

	// accessor function
	double get_value() const { return m_neuron_value; }

	// overloaded insertion and extraction operators
	friend std::ostream& operator<<(std::ostream& output, const InputLayerNeuron& neuron) { return output << neuron.get_value(); }
	friend std::istream& operator>>(std::istream& input, InputLayerNeuron& neuron) { return input >> neuron.m_neuron_value; }

	// overloaded assignment operator
	void operator=(const InputLayerNeuron& neuron) { m_neuron_value = neuron.m_neuron_value; }

private:
	// default constructor is private to prevent the use of the neuron in the input layer without providing a input value
	InputLayerNeuron() { }
};

class OutputLayerNeuron : public HiddenLayerNeuron
{
public:
	OutputLayerNeuron(std::vector<double> range_of_representations, std::vector<std::string> representations);
	OutputLayerNeuron(std::map<std::pair<double, double>, std::string> representation, 
					std::vector<double> input_vectors, std::vector<double> input_weights, double bias) 
		: HiddenLayerNeuron(input_vectors, input_weights, bias), representation_of_neuron(representation) { }

	// accessor function
	double get_value() const { return m_neuron_value; }
	std::string get_value_representation(std::pair<double, double> range_of_value) const { return representation_of_neuron.at(range_of_value); }

	// mutator function
	void set_value(double new_value) { m_neuron_value = new_value; }
	void set_representation(std::pair<double, double> range_of_representation, std::string);

	// overloaded insertion and extraction operator only accesses and modifies the double value and not the string value 
	// contained in the neuron
	friend std::ostream& operator<<(std::ostream& output, const OutputLayerNeuron& neuron) { return output << neuron.m_neuron_value; }
	friend std::istream& operator>>(std::istream& input, OutputLayerNeuron& neuron) { return input >> neuron.m_neuron_value; }

	// overloaded assignment operator modifies both values of the neuron
	void operator=(const OutputLayerNeuron& neuron) { m_neuron_value = neuron.m_neuron_value; representation_of_neuron = neuron.representation_of_neuron; }

private:
	// This member variable maps strings to the range of values that it represents, the range is specified as the values between
    // the first and second double in the pair.
	std::map<std::pair<double, double>, std::string> representation_of_neuron;
};

#endif // ANN_LAYERS_HPP