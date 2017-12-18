#ifndef VECTOR2D_HPP
#define VECTOR2D_HPP

#include <cmath>
#include <iosfwd>
#include <limits>

#include "Utilities/Utilities.hpp"

enum { CLOCKWISE = 1, COUNTER_CLOCKWISE = -1};

struct Vector2D
{
    double x;
    double y;

    Vector2D() : x(0.0), y(0.0) { }
    Vector2D(double a, double b) : x(a), y(b) { }

    // sets x and y to zero
    void zero() { x = 0.0; y = 0.0; }

    // returns true if both x and y are zero
    bool isZero() const { return (x*x + y*y) < MinDouble; }

    // returns the length of the vector
    inline double length() const;

    // returns the squared length of the vector
    inline double length_sq() const;

    inline void normalize();

    inline double dot(const Vector2D& v2) const;

    // returns positive if v2 is clockwise of this vector,
    // negative if counter-clockwise (assuming the y-axis
    // is pointing down, x-axis to the right)
    inline int sign(const Vector2D& v2) const;

    // returns the vector that is perpendicular to the 
    // passed one
    inline Vector2D perpendicular() const;

    // adjusts x and y so that the length of the vector does
    // not exceed max
    inline void truncate(double max);

    // returns the distance between this vector and the one
    // passed as a parameter
    inline double distance(const Vector2D& v2) const;

    inline double distance_sq(const Vector2D& v2) const;

    inline void reflect(const Vector2D& norm);

    // returns the vector that is the revers of this vector
    inline Vector2D get_reverse() const;

    // overloaded operators
    const Vector2D& operator+=(const Vector2D& rhs)
    {
        x += rhs.x;
        y += rhs.y;

        return *this;
    }

    const Vector2D& operator-=(const Vector2D& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;

        return *this;
    }

    const Vector2D& operator*=(const double& rhs)
    {
        x *= rhs;
        y *= rhs;

        return *this;
    }

    const Vector2D& operator/=(const double& rhs)
    {
        x /= rhs;
        y /= rhs;

        return *this;
    }

    bool operator==(const Vector2D& rhs)const
    {
        return (isEqual(x, rhs.x) && isEqual(y,rhs.y) );
    }

    bool operator!=(const Vector2D& rhs)const
    {
        return (x != rhs.x) || (y != rhs.y);
    }
};

inline Vector2D operator*(const Vector2D &lhs, double rhs);
inline Vector2D operator*(double lhs, const Vector2D &rhs);
inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs);
inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs);
inline Vector2D operator/(const Vector2D &lhs, double val);
std::ostream& operator<<(std::ostream& os, const Vector2D& rhs);
std::ifstream& operator>>(std::ifstream& is, Vector2D& lhs);

inline double Vector2D::length() const
{
    return sqrt(x * x + y * y);
}

inline double Vector2D::length_sq() const
{
    return (x * x + y * y);
}

inline double Vector2D::dot(const Vector2D &v2) const
{
    return x*v2.x + y*v2.y;
}

inline int Vector2D::sign(const Vector2D& v2) const
{
    if (y*v2.x > x*v2.y)
    { 
        return COUNTER_CLOCKWISE;
    }
    else 
    {
        return CLOCKWISE;
    }
}

inline Vector2D Vector2D::perpendicular() const
{
    return Vector2D(-y, x);
}

inline double Vector2D::distance(const Vector2D &v2) const
{
    double ySeparation = v2.y - y;
    double xSeparation = v2.x - x;

    return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

inline double Vector2D::distance_sq(const Vector2D &v2) const
{
    double ySeparation = v2.y - y;
    double xSeparation = v2.x - x;

    return ySeparation*ySeparation + xSeparation*xSeparation;
}

inline void Vector2D::truncate(double max)
{
    if (this->length() > max)
    {
        this->normalize();

        *this *= max;
    } 
}

inline void Vector2D::reflect(const Vector2D& norm)
{
    *this += 2.0 * this->dot(norm) * norm.get_reverse();
}

inline Vector2D Vector2D::get_reverse() const
{
    return Vector2D(-this->x, -this->y);
}

inline void Vector2D::normalize()
{ 
    double vector_length = this->length();

    if (vector_length > std::numeric_limits<double>::epsilon())
    {
        this->x /= vector_length;
        this->y /= vector_length;
    }
}

inline Vector2D Vec2DNormalize(const Vector2D &v)
{
    Vector2D vec = v;

    double vector_length = vec.length();

    if (vector_length > std::numeric_limits<double>::epsilon())
    {
        vec.x /= vector_length;
        vec.y /= vector_length;
    }

    return vec;
}

inline double Vec2DDistance(const Vector2D &v1, const Vector2D &v2)
{
    double ySeparation = v2.y - v1.y;
    double xSeparation = v2.x - v1.x;

    return sqrt(ySeparation*ySeparation + xSeparation*xSeparation);
}

inline double Vec2DDistanceSq(const Vector2D &v1, const Vector2D &v2)
{
    double ySeparation = v2.y - v1.y;
    double xSeparation = v2.x - v1.x;

    return ySeparation*ySeparation + xSeparation*xSeparation;
}

inline double Vec2DLength(const Vector2D& v)
{
    return sqrt(v.x*v.x + v.y*v.y);
}

inline double Vec2DLengthSq(const Vector2D& v)
{
    return (v.x*v.x + v.y*v.y);
}

inline Vector2D operator*(const Vector2D &lhs, double rhs)
{
    Vector2D result(lhs);
    result *= rhs;
    return result;
}

inline Vector2D operator*(double lhs, const Vector2D &rhs)
{
    Vector2D result(rhs);
    result *= lhs;
    return result;
}

// overload the - operator
inline Vector2D operator-(const Vector2D &lhs, const Vector2D &rhs)
{
    Vector2D result(lhs);
    result.x -= rhs.x;
    result.y -= rhs.y;
    
    return result;
}

// overload the + operator
inline Vector2D operator+(const Vector2D &lhs, const Vector2D &rhs)
{
    Vector2D result(lhs);
    result.x += rhs.x;
    result.y += rhs.y;
    
    return result;
}

// overload the / operator
inline Vector2D operator/(const Vector2D &lhs, double val)
{
    Vector2D result(lhs);
    result.x /= val;
    result.y /= val;

    return result;
}

#endif // VECTOR2D_HPP