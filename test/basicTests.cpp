#include <gtest/gtest.h>
#include "Particle.hpp"
#include "Point2D.hpp"
#include "Box.hpp"
#include "System.hpp"
#include "Vicsek.hpp"

#include <vector>
#include <iostream>

TEST(basicTests, setterTestPoint2D){
    Point2D p(2.0, 3.0);

    EXPECT_EQ(2.0, p.getX());
    EXPECT_EQ(3.0, p.getY());

    p.setX(4.0);
    EXPECT_EQ(4.0, p.getX());
}

TEST(basicTests, magnitudePoint2D){
    Point2D p(-2.0, 3.0);
    
    EXPECT_EQ(sqrt(4.0 + 9.0), p.magnitude());
}

TEST(basicTests, point2DdiffMagnitude){
    Point2D p(-2.0, 3.0);
    Point2D q(-1.0, 4.0);
    Point2D r = p - q;
    
    EXPECT_EQ(-1.0, r.getX());
    EXPECT_EQ(-1.0, r.getY());
    EXPECT_EQ(sqrt(2), r.magnitude());
}

TEST(basicTests, particleConstructor){

    Point2D rr(1.0, 1.0);
    double th = 20.0;
    Particle particle(rr, th);

    EXPECT_EQ(20.0, particle.theta);
}

TEST(basicTests, boxConstructor){
    Point2D size(3.0, 3.0);
    Box boxx(size);
    
    EXPECT_EQ(-1.5, boxx.Lmin.getX());
    EXPECT_TRUE(-boxx.Lmin.getX() == boxx.Lmax.getX());
    EXPECT_TRUE(-boxx.Lmin.getY() == boxx.Lmax.getY());
}

TEST(basicTests, systemConstructor){
    Point2D rr(0.0, 0.0);
    double th = 20.0;
    Particle par(rr, th);

    std::vector <Particle> particlesList;
    particlesList.emplace_back(par);

    Point2D size(3.0, 3.0);
    Box boxx(size);
    
    System system(boxx, particlesList);
    
    EXPECT_EQ(20.0, system._particlesList.at(0).theta);
    EXPECT_EQ(-1.5, system.getBox().Lmin.getX());
}

TEST(basicTests, applyPeriodic){
    Point2D rr(0.0, 0.0);
    Point2D nn(0.0, 1.0);
    double th = 20.0;
    Particle par(rr, th);

    std::vector <Particle> particlesList;
    particlesList.emplace_back(par);

    Point2D size(6.0, 6.0);
    Box boxx(size);
    
    System system(boxx, particlesList);
    Point2D p(4.0, 4.0);

    system._particlesList.at(0).r = system._particlesList.at(0).r + p;
    system.applyPeriodic();
    
    EXPECT_EQ(-2.0, system._particlesList.at(0).r.getX());
}

TEST(basicTests, VicseckGetterSetters){
    Point2D rr(0.0, 0.0);
    Point2D nn(0.0, 1.0);
    double th = 20.0;
    Particle par(rr, th);

    std::vector <Particle> particlesList;
    particlesList.emplace_back(par);

    Point2D size(6.0, 6.0);
    Box boxx(size);
    
    System system(boxx, particlesList);
    Vicsek solver(system);
    
    double R = 2.0, dt = 0.01; 
    solver.setR(R);
    solver.setdt(dt);

    EXPECT_EQ(2.0, solver.getR());
    EXPECT_EQ(0.01, solver.getdt());
}

TEST(basicTests, thetaAveragerNoPBC){
    // TO FIX: this terrible one by one creation of particle list
    // I want to have DRY code here
    Point2D pt1(-2.0, 2.0);
    Point2D pt2(-1.0, 1.0);
    Point2D pt3(1.0, 1.0);
    Point2D pt4(-2.0, -1.0);
    Point2D pt5(1.0, -1.0);
    Point2D pt6(0.0, 0.0);

    Point2D nn(0.0, 1.0);
    double th1 = 20.0;
    double th2 = 15.0;
    double th3 = -40.0;
    double th4 = 60.0;
    double th5 = -60.0;
    double th6 = -30.0;

    Particle p1(pt1, th1);
    Particle p2(pt2, th2);
    Particle p3(pt3, th3);
    Particle p4(pt4, th4);
    Particle p5(pt5, th5);
    Particle p6(pt6, th6);

    std::vector <Particle> particlesList{p1, p2, p3, p4, p5, p6};

    Point2D size(6.0, 6.0);
    Box boxx(size);
    
    System system(boxx, particlesList);
    Vicsek solver(system);

    double R = 2.0;
    solver.setR(R);

    EXPECT_EQ(-8.75, solver.getAverageTheta(system._particlesList.at(1)));
}

TEST(basicTests, thetaAveragerPBC){
    // TO FIX: this terrible one by one creation of particle list
    // I want to have DRY code here
    Point2D pt1(-2.0, 2.0);
    Point2D pt2(-2.5, 2.0);
    Point2D pt3(2.0, -2.0);
    Point2D pt4(1.0, 1.0);

    double th1 = 20.0;
    double th2 = 15.0;
    double th3 = -40.0;
    double th4 = -359.0;

    Particle p1(pt1, th1);
    Particle p2(pt2, th2);
    Particle p3(pt3, th3);
    Particle p4(pt4, th4);

    std::vector <Particle> particlesList{p1, p2, p3, p4};

    Point2D size(6.0, 6.0);
    Box boxx(size);
    
    System system(boxx, particlesList);
    Vicsek solver(system);

    double R = 2 * sqrt(2) + 0.1;
    solver.setR(R);

    EXPECT_EQ(-5.0/3.0, solver.getAverageTheta(system._particlesList.at(2)));
    EXPECT_EQ(-5.0/3.0, solver.getAverageTheta(system._particlesList.at(0)));
}

TEST(basicTests, pbcDistanceCorrect){

    Point2D pt1(-2.5, 0.0);
    Point2D pt2(2.0, 0.0);

    double th1 = 20.0;
    double th2 = 15.0;

    Particle p1(pt1, th1);
    Particle p2(pt2, th2);

    std::vector <Particle> particlesList{p1, p2};

    Point2D size(6.0, 6.0);
    Box boxx(size);
    
    System system(boxx, particlesList);
    Vicsek solver(system);

    double R = 1.7;
    solver.setR(R);

    EXPECT_FLOAT_EQ(17.5, solver.getAverageTheta(system._particlesList.at(1)));
    EXPECT_FLOAT_EQ(17.5, solver.getAverageTheta(system._particlesList.at(0)));

}

TEST(basicTests, evolverFirstStepNONOISE){

    Point2D pt1(1.0, 2.0);
    Point2D pt2(1.0, 1.0);
    Point2D pt3(-2.0, 0.0);
    Point2D pt4(1.0, -2.0);

    double th1 = 200.0 * (M_PIl/180.0);
    double th2 = -150.0 * (M_PIl/180.0);
    double th3 = 1.0 * (M_PIl/180.0);
    double th4 = 20.0 * (M_PIl/180.0);

    Particle p1(pt1, th1);
    Particle p2(pt2, th2);
    Particle p3(pt3, th3);
    Particle p4(pt4, th4);

    std::vector <Particle> particles{p1, p2, p3, p4};

    Point2D size(6.0, 6.0);
    Box box(size);

    System system(box, particles);
    Vicsek solver(system);

    double R = 1.0;
    double v0 = 1.0;
    double dt = 0.2;
    solver.setR(R);
    solver.setv0(v0);
    solver.setdt(dt);

    EXPECT_DOUBLE_EQ(1.0, solver.getSystem()._particlesList.at(0).r.getX());
    EXPECT_DOUBLE_EQ(2.0, solver.getSystem()._particlesList.at(0).r.getY());

    solver.evolver(1, 0);

    EXPECT_NEAR(1.18126, solver.getSystem()._particlesList.at(0).r.getX(), 0.00001);
    EXPECT_NEAR(2.08452, solver.getSystem()._particlesList.at(0).r.getY(), 0.00001);
}
