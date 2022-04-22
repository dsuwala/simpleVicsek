#include "Vicsek.hpp"


double Vicsek::getAverageTheta(Particle &particle){

    double neighborTheta = 0.0;
    int neighbor_number = 0;

    for (Particle &par : system._particlesList){
        Point2D rij = par.r - particle.r; 
        double rij_x = rij.getX();
        double rij_y = rij.getY();
        double boxSizeX = system.getBox().L.getX();
        double boxSizeY = system.getBox().L.getY();

        if (rij_x > boxSizeX * 0.5 ) rij.setX(rij_x - boxSizeX);
        if (rij_x <= - boxSizeX * 0.5 ) rij.setX(rij_x + boxSizeX);

        if (rij_y > boxSizeY * 0.5 ) rij.setY(rij_y - boxSizeY);
        if (rij_y <= - boxSizeY * 0.5 ) rij.setY(rij_y + boxSizeY);

        if ( rij.magnitude() <= _R){
            neighborTheta += par.theta;
            neighbor_number++;
        }

    }
    return neighborTheta / neighbor_number;
}

void Vicsek::evolver(const int steps, const double noise){
    
    RandomClass random(12312313);
    // initialize prev step
    std::vector <Particle> prev_step;

    for (int i = 0; i < steps; i++){

        prev_step = system._particlesList;
//        std::cerr << i << '\n';
        // loop over all particles
        for (int n = 0; n < prev_step.size(); n++){

            double avg_theta = getAverageTheta(prev_step.at(n)) + random.randreal(- noise / 2., noise / 2.);
            //double avg_theta = getAverageTheta(prev_step.at(n));

            // update director 
            system._particlesList.at(n).n = Point2D(std::cos(avg_theta), std::sin(avg_theta));

            //move along director: workaround with tmp variable v0theta as 
            // scalar multiplication seems not to work as expected
            Point2D v0theta = Point2D(std::cos(avg_theta) * (_v0 * _dt), std::sin(avg_theta) * (_v0 * _dt));
            system._particlesList.at(n).r = prev_step.at(n).r + v0theta;


        }
        system.applyPeriodic();
    }

}
