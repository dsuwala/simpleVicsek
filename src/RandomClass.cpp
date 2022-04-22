#include "RandomClass.hpp"

double RandomClass::rand(){

    std::uniform_real_distribution<double> rnd_uniform_real_distribution(0.0, 1.0);
    // std::mt19937 *engine = &RandomClass::getRandomEngine();

    return rnd_uniform_real_distribution(_randomEngine);
}

double RandomClass::randreal(double low, double high){

    std::uniform_real_distribution<double> rnd_uniform_real_distribution(low, high);
    // std::mt19937 *engine = &RandomClass::getRandomEngine();

    return rnd_uniform_real_distribution(_randomEngine);
}
        
int RandomClass::randint(int low, int high){

    RandomClass::getUniformInt().param(
        std::uniform_int_distribution<int>::param_type(low, high)
    );
    
    return RandomClass::getUniformInt()(_randomEngine);
}

double RandomClass::randn(double mean, double variance){
    RandomClass::getNormal().param(
        std::normal_distribution<double>::param_type(mean, variance)
    );
    // std::mt19937 *engine = &RandomClass::getRandomEngine();
    
    return RandomClass::getNormal()(_randomEngine);
}
