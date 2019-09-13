#ifndef PARTICLESYSTEM
#define PARTICLESYSTEM
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include "particle.h"

using namespace std;
using namespace Eigen;

class System{
private:
  vector<Particle*> particles;  //All particles
  int N;  //Amount of particles

  Vector3d box; //Box dimensions

  Vector3d (*force_function)(Particle *p1, Particle *p2) = [](Particle *p1, Particle *p2) {return  Vector3d(0,0,0);};
  double (*potential_function)(Particle *p1, Particle *p2) = [](Particle *p1, Particle *p2) {return  0.0;};

  double potential_energy;  //Potential energy of system
  double kinetic_energy;  //Kinetic energy of system

  double dt = 0.01; //Timestep
  double t = 0; //Time passed
public:
  System(int amount_of_particles,
    Vector3d box_dimensions,
    double start_velocity);

  System(int amount_of_particles,
    Vector3d box_dimensions,
    double start_velocity,
    Vector3d (*force)(Particle *p1, Particle *p2));

  System(int amount_of_particles,
    Vector3d box_dimensions,
    double start_velocity,
    Vector3d (*force)(Particle *p1, Particle *p2),
    double (*potential)(Particle *p1, Particle *p2));

    System(int amount_of_particles,
      Vector3d box_dimensions,
      double r,
      double start_velocity);

    System(int amount_of_particles,
      Vector3d box_dimensions,
      double start_velocity,
      double r,
      Vector3d (*force)(Particle *p1, Particle *p2));

    System(int amount_of_particles,
      Vector3d box_dimensions,
      double start_velocity,
      double r,
      Vector3d (*force)(Particle *p1, Particle *p2),
      double (*potential)(Particle *p1, Particle *p2));

  void wall_collision(int i);

  bool collision_check(int i, int j);

  void collision(int i, int j);

  void update_system();

  double get_kinetic() {return kinetic_energy;}
  double get_potential() {return potential_energy;}
  double get_time() {return t;}

  void calc_kinetic();
  void calc_potential();

  vector<double> get_kinetic_distribution();
  vector<double> get_potential_distribution();

  vector<Vector3d> get_particle_positions();


};


#endif
