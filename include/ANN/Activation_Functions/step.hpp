#ifndef STEP_HPP
#define STEP_HPP

struct Step
{
    /*-------------------------------------------------------------------------
        Implements the piecewise function

        y(x) = { 1 if x >= 0, 0 if x < 0 }

        Returns true if x >= 0 and returns false if x < 0
    --------------------------------------------------------------------------*/
    bool step_function(int x)
    {
        if (x >= 0)
        {
            return true;
        }

        return false;
    }
};

#endif // STEP_HPP