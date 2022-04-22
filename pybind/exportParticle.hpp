#ifndef __export_particle_hpp__
#define __export_particle_hpp__

#include "Particle.hpp"
#include <vector>

void exportParticle(py::module m){ 

    py::class_<Particle>(m ,"Particle")

        .def(py::init<Point2D&, double&>())

        .def_readwrite("r", &Particle::r)
        .def_readwrite("n", &Particle::n)
        .def_readwrite("theta", &Particle::theta);
}

void exportParticleVector(py::module &m)
{
    py::class_<std::vector<Particle>>(m, "ParticleList")
        .def(py::init<>())
        .def("clear", &std::vector<Particle>::clear)
        .def("pop_back", &std::vector<Particle>::pop_back)

        .def("append", (void (std::vector<Particle>::*)(const Particle &)) &std::vector<Particle>::push_back)
        .def("__len__", [](const std::vector<Particle> &v) { return v.size(); })

        .def("__iter__", [](std::vector<Particle> &v) {
            return py::make_iterator(v.begin(), v.end());}, 
            py::keep_alive<0, 1>())

        .def("__getitem__", [](const std::vector<Particle> &v, size_t i){
            if (i >= v.size ()) throw py::index_error(); return v[i]; })

        .def("__setitem__", [](std::vector<Particle> &v, size_t i, Particle &d) { if (i >= v.size()) throw py::index_error(); v[i] = d;});
}

#endif
