#ifndef __point2d_hpp__
#define __point2d_hpp__

#include <cmath>

class Point2D{
    public:
        /*! Create 2D vector of doubles witch supported vector operations: magnitude, 
        vector addition/subtraction +/-, dot product *, vector boolean comparison by magnitude >/< and 
        scaling by scalar *= and /=
        */
        Point2D(double x, double y);
        Point2D(){};

        ~Point2D(){}

        double magnitude();
        
        /*! Performs elementwise addition of vector elements and returns new vector
        */
        Point2D operator+(Point2D &other);

        /*! Performs elementwise subtraction of provided vector from target vector
        and returns new vector
        */
        Point2D operator-(Point2D &other);

        /*! Returns new vector as dot product of two provided vectors 
        */
        double operator*(Point2D &other); 

        /*! Returns true if target vector has smaller magnitude than other provided as 
        an argument
        */ 
        bool operator<(Point2D &other);

        /*! Returns true if target vector has greater magnitude than 
        other provided as an argument
        */ 
        bool operator>(Point2D &other);

        /*! Performs elementwise division of targed vector by provided scalar
        */
        Point2D operator/=(double &other); 
        // Point2D operator/=(int &other); 

        /*! Performs elementwise division of targed vector by provided scalar
        */
        Point2D operator*=(double &other);
        // Point2D operator*=(int &other);


        double getX(){return _x;}
        double getY(){return _y;}
        double setX(double x){return _x = x;}
        double setY(double y){return _y = y;}
    private:
        double _x;
        double _y; 
};
#endif /* VECTORCLASS_HPP */
