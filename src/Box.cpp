#include "Box.hpp"

Box::Box(Point2D &l){
    this->L = l;

    Lmax.setX(l.getX() / 2.0);
    Lmax.setY(l.getY() / 2.0);

    Lmin.setX(- l.getX() / 2.0);
    Lmin.setY(- l.getY() / 2.0);
}