#include "Point2D.hpp"

Point2D::Point2D(double x, double y){
    Point2D::setX(x);
    Point2D::setY(y);
}

double Point2D::magnitude(){
    return std::sqrt(_x * _x + _y * _y);
}

Point2D Point2D::operator+(Point2D &other){
    return Point2D(Point2D::getX() + other.getX(),
                       Point2D::getY() + other.getY());
}

Point2D Point2D::operator-(Point2D &other){
    return Point2D(Point2D::getX() - other.getX(),
                   Point2D::getY() - other.getY());
}

double Point2D::operator*(Point2D &other){
    return Point2D::getX() * other.getX() + 
           Point2D::getY() * other.getY();
}

bool Point2D::operator<(Point2D &other){
    double own_magnitude = magnitude();
    double other_magnitude = other.magnitude();
    if (own_magnitude >= other_magnitude){
        return false;
    }else{
        return true;
    }
}

bool Point2D::operator>(Point2D &other){
    double own_magnitude = magnitude();
    double other_magnitude = other.magnitude();
    if (own_magnitude > other_magnitude){
        return true;
    }else{
        return false;
    }
}

Point2D Point2D::operator/=(double &other){
    return Point2D(Point2D::getX() / other,
                       Point2D::getY() / other);
}

Point2D Point2D::operator*=(double &other){
    return Point2D(Point2D::getX() * other,
                       Point2D::getY() * other);
}
