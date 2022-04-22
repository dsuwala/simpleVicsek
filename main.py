from activeSolver import Box, Vicsek, System, Particle, Point2D, ParticleList
import math
import numpy as np
import vtk


def dump_vtp(p,outfile):
  """
    Output the system as a VTP file for direct visualisation in ParaView.
    Parameter
    ---------
      outfile : string
        Name of the output file.
    Note
    ----
      Caller should ensure that the file has correct extension
  """

  points = vtk.vtkPoints()
  ids = vtk.vtkIntArray()
  n = vtk.vtkDoubleArray()
  v = vtk.vtkDoubleArray()
  f = vtk.vtkDoubleArray()
  radius = vtk.vtkDoubleArray()
  ids.SetNumberOfComponents(1)
  n.SetNumberOfComponents(3)
  v.SetNumberOfComponents(3)
  f.SetNumberOfComponents(3)
  radius.SetNumberOfComponents(1)
  ids.SetName("id")
  n.SetName("director")
  v.SetName("velocity")
  f.SetName("force")
  radius.SetName("radius")
  for i in range(p.N):
    points.InsertNextPoint([p.r[i].x, p.r[i].y, 0.0])
    ids.InsertNextValue(i)
    n.InsertNextTuple([p.n[i].x, p.n[i].y, 0.0])
    v.InsertNextTuple([p.v[i].x, p.v[i].y, 0.0])
    f.InsertNextTuple([p.force[i].x, p.force[i].y, 0.0])
    radius.InsertNextValue(p.radius[i])


  polyData = vtk.vtkPolyData()
  polyData.SetPoints(points)
  polyData.GetPointData().AddArray(ids)
  polyData.GetPointData().AddArray(n)
  polyData.GetPointData().AddArray(v)
  polyData.GetPointData().AddArray(f)
  polyData.GetPointData().AddArray(radius)
  writer = vtk.vtkXMLPolyDataWriter()
  writer.SetFileName(outfile)
  if vtk.VTK_MAJOR_VERSION <= 5:
      writer.SetInput(polyData)
  else:
      writer.SetInputData(polyData)
  writer.SetDataModeToAscii()
  writer.Write()



def main():
    points = [Point2D(1.0, 2.0), Point2D(1.0, 1.0), Point2D(-2.0, 0.0), Point2D(1.0, -2.0)]

    conv =  math.pi / 180.
    thetas = [200.0 * conv, -150.0 * conv, 1.0 * conv, 20.0 * conv]

    particles = ParticleList()
    for n in range(0, len(points)):
        particles.append(Particle(points[n], thetas[n]))

    size = Point2D(6.0, 6.0)
    box  = Box(size)
    system = System(box, particles)

    solver = Vicsek(system)

    solver.R = 1.0
    solver.v0 = 1.0
    solver.dt = 0.2

    print(solver.getSystem().particlesList[0].r.x)

    solver.evolver(1)

    print(solver.getSystem().particlesList[0].r.x)


if __name__ == "__main__":
        main()


