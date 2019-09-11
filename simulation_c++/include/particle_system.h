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
  vector<Particle*> particles;
  int N;

  Vector3d box;

  double potential_energy;
  double kinetic_energy;
public:
  System(int amount_of_particles,
    Vector3d box_dimensions,
    double start_velocity);

  void wall_collision(int i);

  bool collision_check(int i, int j);

  void collision(int i, int j);

};


#endif
