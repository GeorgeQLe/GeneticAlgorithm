/*  Copyright 2017 George Le

*/
#ifndef ACTIVATION_FUNCTIONS_HPP
#define ACTIVATION_FUNCTIONS_HPP

#include "Activation_functions_types.hpp"

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