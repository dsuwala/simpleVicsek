#ifndef __export_viscek_hpp__
#define __export_viscek_hpp__

#include "Vicsek.hpp"
#include <vector>

void exportVicsek(py::module m){ 
    py::class_<Vicsek>(m ,"Vicsek")

        .def(py::init<System&>())

        .def_property("R", &Vicsek::getR, &Vicsek::setR)
        .def_property("dt", &Vicsek::getdt, &Vicsek::setdt)
        .def_property("v0", &Vicsek::getv0, &Vicsek::setv0)

        .def("getSystem", &Vicsek::getSystem)
        .def("evolver", &Vicsek::evolver);
}

#endif
