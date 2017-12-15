#ifndef ACTIVATION_FUNCTIONS_HPP
#define ACTIVATION_FUNCTIONS_HPP

#include "step.hpp"
#include "sigmoid.hpp"

template<class ActivationFunctionType>
class Activation_function
{
    public:
    Activation_function() :m_value(0) { }

    ActivationFunctionType m_activation_function;

    private:
    double m_value;
};

#endif // ACTIVATION_FUNCTIONS_HPP