#include "ANN/Neurons/ANN_layers.hpp"

void HiddenLayerNeuron::calculate_output(Activation_function<Sigmoid> function)
{
    m_neuron_value = function.m_activation_function.sigmoid_function(summation_weight_input_vector());
}

double HiddenLayerNeuron::summation_weight_input_vector()
{
	m_summation = 0.0;

	if ((m_input_vectors.size() == m_input_weight.size()) && (m_input_vectors.size() > 0 && m_input_weight.size() > 0))
	{
		for(unsigned int i = 0; i < m_input_vectors.size(); ++i)
		{
			m_summation += (m_input_vectors.at(i) * m_input_weight.at(i) + m_bias);
		}
	}
	return m_summation;
}