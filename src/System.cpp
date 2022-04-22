#include "System.hpp"

void System::applyPeriodic(){

    for (Particle& par : _particlesList){

        double rx = par.r.getX();
        double ry = par.r.getY();

        if (rx < _box.Lmin.getX()) par.r.setX(rx + _box.L.getX());
        if (rx > _box.Lmax.getX()) par.r.setX(rx - _box.L.getX());
    }

}
