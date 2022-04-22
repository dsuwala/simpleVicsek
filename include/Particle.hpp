#ifndef __particle_hpp__
#define __particle_hpp__

#include "Point2D.hpp"
#include <cmath>

struct Particle
{
    
    // int id;
    Point2D r; // position
    Point2D n; // direction vector (|n| = 1)
    double theta; //direction

    Particle(Point2D &rr, double &th) : r(rr), theta(th), n(Point2D(std::cos(theta), std::sin(theta))){}
};


#endif
