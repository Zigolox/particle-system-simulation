#include <iostream>
#include <fstream>
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
  Vector3d box = {256,256,256};
  double vel = 800;
  System particle_system(N,
    box,
    vel,
    1.0);
  vector<double> EK;
  vector<double> EP;
  vector<double> t;
  vector<double> Energy_distribution;
  vector<vector<Vector3d>> particle_positions;

  for(int i = 0; i < 1000; i++) {
    particle_system.update_system();

    if(i%5 == 0) {
      std::cout << "Progress: " << (float) i/10000  << '\n';

      particle_system.calc_kinetic();

      EK.push_back(particle_system.get_kinetic());

      particle_positions.push_back(particle_system.get_particle_positions());

      t.push_back(particle_system.get_time());




    }

  }
  ofstream energy_file;
  ofstream position_file;
  energy_file.open("energy_data.txt");
  energy_file.open("position_data.txt");
  Energy_distribution = particle_system.get_kinetic_distribution();

  for (double val : EK) {
    energy_file << val << '\t';
  }
  energy_file << '\n';


  for (double val : t) {
    energy_file << val << '\t';
    position_file << val << '\t';
  }
  energy_file << '\n';

  position_file << '\n';

  for (vector<Vector3d> all_positions : particle_positions) {
    for (Vector3d pos : all_positions) {
      position_file << pos[0] << " " << pos[1] << " " << pos[2] << "\t";
    }
    position_file << "\n";
  }

  for (double val : Energy_distribution) {
    energy_file << val << '\t';
  }

energy_file.close();
position_file.close();




  return 0;
}
