#include <iostream>
#include <cmath>
#include <armadillo>
#include <stdlib.h>
#include <time.h>
#include "particle.h"
#include "particle_system.h"
#define PI 3.14159265358979323846

int main(int argc, char const *argv[]) {
  srand(time(NULL));
  Vector3d box = {10,20,30};
  double vel = 2;
  Particle p1(box, vel);
  p1.print_data();
  return 0;
}
