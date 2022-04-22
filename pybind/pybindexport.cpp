#ifndef __pybindexport_hpp__
#define __pybindexport_hpp__

#include <pybind11/pybind11.h>

namespace py = pybind11;

//types
#include "exportPoint2D.hpp"
#include "exportBox.hpp"
#include "exportParticle.hpp"
#include "exportSystem.hpp"
#include "exportVicsek.hpp"

PYBIND11_MODULE(activeSolver, m)
{
    ///Documentation
    m.doc() = R"pbdoc(
        Test A
        -----------------------
        .. author:: your name here
        .. currentmodule:: your module name here
        .. autosummary::
           :toctree: _generate
    )pbdoc";
    m.attr("__version__") = "1.0";

    //This is how we export the classes
    exportPoint2D(m);
    exportPoint2Dvector(m);
    exportBox(m);

    exportParticle(m);
    exportParticleVector(m);
    exportSystem(m);
    exportVicsek(m);
}

#endif

