#include <iostream>
#include <cmath>
#include <armadillo>
#include <stdlib.h>
#include <time.h>
#include "particle.h"
#include "particle_system.h"
#define pi 3.14159265358979323846
#define epsilon 8.85e-3 //F/nm

Vector3d electrical_force(Particle *p1, Particle *p2) {
  Vector3d pos1, pos2, r_vec;
  double r;
  Vector3d F;
  pos1 = p1 -> get_position();
  pos2 = p2 -> get_position();
  r_vec = pos2 - pos1;
  r = sqrt(r_vec.dot(r_vec));
  F = -1/(4*pi*epsilon)*r_vec/(r*r*r);
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
  U = 1/(4*pi*epsilon)/(r);
  return U;
}

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  Vector3d box = {10,20,30};
  double vel = 2;
  Particle p1(box, vel);
  p1.print_data();
  double (*force_function)(Particle *p1, Particle *p2);
  force_function = [](Particle *p1, Particle *p2) {return  0.0;};
  return 0;
}
