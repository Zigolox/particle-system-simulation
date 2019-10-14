#ifndef SUPERSYSTEM
#define SUPERSYSTEM

#include <stdlib.h>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include "system.h"

using namespace std;
using namespace Eigen;

class Super_System {
private:
  vector<super_system *> subsystems;
  vector<System *> lowest_systems;

  Vector3d (* int_loc_force)(Vector3d *r1, Vector3d *r2);
  Vector3d (* ext_loc_force)(Vector3d *r1, Vector3d *r2);
  Vector3d (* ext_glob_force)(Vector3d *r1, Vector3d *r2);

  double t_local;
  double *t_global;
  double dt_local;

public:
  Super_System(int N){

  }
  double get_timestep(){return dt_local;}
  double get_smallest_timestep();
  void set_timestep(double dt) {dt_local = dt;}
};

#endif
