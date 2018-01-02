/*  Copyright 2017 George Le

*/
#ifndef ACTIVATION_FUNCTIONS_TYPES_HPP
#define ACTIVATION_FUNCTIONS_TYPES_HPP

#include <cmath>

struct Sigmoid 
{
    Sigmoid() { }
    
    /*---------------------------------------------------------------------
	    Sigmoid Implementation

	    Function that implements the following function, with input x

	    y = 1/(1-e^-x)

	    And returns a double percision value y between 1 and 0
	----------------------------------------------------------------------*/
	double sigmoid_function(double x) {
        return (1.0 / (1.0 + exp(-x)));
    }
};

struct Step 
{
    /*-------------------------------------------------------------------------
        Implements the piecewise function

        y(x) = { 1 if x >= 0, 0 if x < 0 }

        Returns true if x >= 0 and returns false if x < 0
    --------------------------------------------------------------------------*/
    bool step_function(int x) {
        if (x >= 0)
        {
            return true;
        }
        return false;
    }
};

#endif // ACTIVATION_FUNCTIONS_TYPES_HPP