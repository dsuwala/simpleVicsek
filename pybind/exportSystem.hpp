#ifndef __export_system_hpp__
#define __export_system_hpp__

#include "System.hpp"
#include "Particle.hpp"
#include "System.hpp"

void exportSystem(py::module &m)
{
    py::class_<System>(m, "System")
        .def(py::init<Box&, std::vector<Particle> &>())

        .def_readwrite("particlesList", &System::_particlesList);
        //.def_readwrite("box", &System::box);
}

#endif
