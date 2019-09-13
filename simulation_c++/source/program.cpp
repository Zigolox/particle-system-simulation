#include <iostream>
#include <cmath>
#include <armadillo>
#include <stdlib.h>
#include <time.h>
#include "particle.h"
#include "particle_system.h"
#define pi 3.14159265358979323846
#define epsilon 1.5e-3 //e^2*ns^2*u^-1*nm^-3
/*
Unit of length: nm
Unit of time: 1e-12s
Unit of charge: e
Unit of mass: u
*/

Vector3d electrical_force(Particle *p1, Particle *p2) {
  Vector3d pos1, pos2, r_vec;
  double r;
  Vector3d F;
  pos1 = p1 -> get_position();
  pos2 = p2 -> get_position();
  r_vec = pos1 - pos2;
  r = sqrt(r_vec.dot(r_vec));
  F = 1*r_vec/(r*r*r);
  return F;
}
double electrical_potential(Particle *p1, Particle *p2) {
  Vector3d pos1, pos2, r_vec;
  double r;
  double U;
  pos1 = p1 -> get_position();
  pos2 = p2 -> get_position();
  r_vec = pos2 - pos1;
  r = sqrt(r_vec.dot(r_vec));
  U = -1/(r);
  return U;
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  int N = 200;
  Vector3d box = {32,32,32};
  double vel = 4;
  System particle_system(N,
    box,
    vel,
    3.0,
    &electrical_force,
    &electrical_potential);
  vector<double> EK;
  vector<double> EP;
  vector<double> t;

  for(int w = 0; w < 20000; w++) {
    particle_system.update_system();

    if(w%1 == 0) {

      particle_system.calc_kinetic();

      particle_system.calc_potential();

      EK.push_back(particle_system.get_kinetic());
      EP.push_back(particle_system.get_potential());

      t.push_back(particle_system.get_time());


    }

  }

  for (double v : EK) {
    std::cout << v << '\t';
  }
  std::cout << '\n';

  for (double v : EP) {
    std::cout << v << '\t';
  }
  std::cout << '\n';

  for (double v : t) {
    std::cout << v << '\t';
  }
  std::cout << '\n';



  return 0;
}
