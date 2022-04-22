#ifndef __box_hpp__
#define __box_hpp__

#include "Point2D.hpp"

struct Box
{
    Point2D L;
    Point2D Lmin; 
    Point2D Lmax;
    
    Box(Point2D &l);
    Box(){};
};

#endif