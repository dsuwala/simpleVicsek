#ifndef __system_hpp__
#define __system_hpp__

#include <vector> 
#include "Particle.hpp"
#include "Box.hpp"

class System
{

    public:
        System(Box &boxx) : _box{boxx}, _numparticles{0}{_particlesList.clear();}
        System(Box &boxx, std::vector<Particle> &p) : _box{boxx}, _numparticles{p.size()}, _particlesList{p}{};
        ~System(){}

        // * Apply pbc for entire particle list
        void applyPeriodic();

        //void addParticle(Particle& p)
        //std::vector <Particle> getParticles() const {return _particlesList;}
        //void setParticles()
        Box getBox() const {return _box;}

        std::vector <Particle> _particlesList;
    private:
        Box& _box;
        long unsigned int _numparticles;
};


#endif
