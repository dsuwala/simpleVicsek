#ifndef __vicsek_hpp__
#define __vicsek_hpp__

#define M_PIl          3.141592653589793238462643383279502884L /* pi */

#include "System.hpp"
#include "Particle.hpp"
#include "Point2D.hpp"
#include "RandomClass.hpp"

#include <vector>
#include <cmath>

#include <iostream>

class Vicsek{
    public:

        // possible probles: empty system
        Vicsek(System &s) : system(s){};
        void evolver(const int steps, const double noise);

        // returns theta averaged over nearest neighbors in 
        // ratius R for each particle
        double getAverageTheta(Particle &particle);
        
        double getR() const {return _R;}
        double getdt() const {return _dt;}
        double getv0() const {return _v0;}
        void setR(double &R) {_R = R;}
        void setdt(double &dt) {_dt = dt;}
        void setv0(double &v0) { _v0 = v0;}

        System& getSystem() const {return system;}

    private:
        System& system;
        
        // neighbor distance with default value
        double _R = 0.5; 
        double _dt = 0.1;
        double _v0 = 0.5;

};



#endif
