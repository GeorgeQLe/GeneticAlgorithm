#ifndef USEFUL_CONSTANTS_HPP
#define USEFUL_CONSTANTS_HPP

#include <limits>

const int     MaxInt    = (std::numeric_limits<int>::max)();
const double  MaxDouble = (std::numeric_limits<double>::max)();
const double  MinDouble = (std::numeric_limits<double>::min)();
const float   MaxFloat  = (std::numeric_limits<float>::max)();
const float   MinFloat  = (std::numeric_limits<float>::min)();

const double   Pi        = 3.14159;
const double   TwoPi     = Pi * 2;
const double   HalfPi    = Pi / 2;
const double   QuarterPi = Pi / 4;

#endif // USEFUL_CONSTANTS_HPP