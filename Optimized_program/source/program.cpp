#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>
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

int N = 1000;
double L = 4;
float exponent = -2;
float constant = 1;
double vel = 1;
float r = 0.01;
int Iterations = 10000;
bool display_progress = 0;
double dt = 0.000001;
string dir_path = "./";
string pos_filename = "position_data.txt";
string energy_filename = "energy_data.txt";
string input_filename = "input_data.txt";
int save_freq = 10;
int print_freq = 100;



Vector3d general_force(Vector3d pos1, Vector3d pos2, float n, float k) {
  Vector3d r_vec;
  double r;
  Vector3d F;

  r_vec = pos2 - pos1;
  r = r_vec.dot(r_vec);
  F = k*(pow(r,(n-1)/2.0))*r_vec;
  return F;
}

double general_potential(Vector3d pos1, Vector3d pos2, float n, float k) {
  Vector3d r_vec;
  double r;
  double U;

  r_vec = pos2 - pos1;
  r = r_vec.norm();
  if(n != -1){
    U = k*(pow(r,n+1))/(n+1);
  }
  else {
    U = k * log(r);
  }
  return U;
}

Vector3d force(Vector3d pos1, Vector3d pos2){
  return general_force(pos1, pos2, exponent, constant);
}

double potential(Vector3d pos1, Vector3d pos2) {
  return general_potential(pos1, pos2, exponent, constant);
}

void argparse(int argc, char const **argv) {
  for(int i = 1; i < argc; i++) {
    if(strcmp(argv[i],"-N") == 0) {
      N = atoi(argv[i+1]);
      i += 1;
    }
    else if(strcmp(argv[i],"-L") == 0) {
      L = atof(argv[i+1]);
      i += 1;
    }
    else if(strcmp(argv[i],"-I") == 0) {
      Iterations = atoi(argv[i+1]);
      i += 1;
    }
    else if(strcmp(argv[i],"-e") == 0) {
      exponent = atof(argv[i+1]);
      i += 1;
    }
    else if(strcmp(argv[i],"-v") == 0) {
      vel = atof(argv[i+1]);
      i += 1;
    }
    else if(strcmp(argv[i],"-r") == 0) {
      r = atof(argv[i+1]);
      i += 1;
    }
    else if(strcmp(argv[i],"-c") == 0) {
      constant = atof(argv[i+1]);
      i += 1;
    }
    else if(strcmp(argv[i],"-t") == 0) {
      dt = atof(argv[i+1]);
      i += 1;
    }
    else if(strcmp(argv[i],"-f") == 0) {
      pos_filename = argv[i+1] + pos_filename;
      energy_filename = argv[i+1] + energy_filename;
      input_filename = argv[i+1] + input_filename;
      i += 1;
    }
    else if(strcmp(argv[i],"-p") == 0) {
      display_progress = 1;
      print_freq = atoi(argv[i+1]);

    }
    else if(strcmp(argv[i],"-s") == 0) {
      save_freq = atoi(argv[i+1]);
    }
    else if(strcmp(argv[i],"-d") == 0) {
      dir_path = argv[i+1];
    }
  }
}


void write_input() {
  std::cout << "#######Input Data#######" << '\n';
  std::cout << "N: " << N << '\n';
  std::cout << "L: " << L << '\n';
  std::cout << "Exponent: " << exponent << '\n';
  std::cout << "Constant: " << constant << '\n';
  std::cout << "Velocity: " << vel << '\n';
  std::cout << "Radius: " << r << '\n';
  std::cout << "Iterations: " << Iterations << '\n';
  std::cout << "Time step: " << dt << '\n';
  std::cout << "########################" << '\n';

}

void write_input(string filename) {
  ofstream file(filename);
  file << "#######Input Data#######" << '\n';
  file << "N: " << N << '\n';
  file << "L: " << L << '\n';
  file << "Exponent: " << exponent << '\n';
  file << "Constant: " << constant << '\n';
  file << "Velocity: " << vel << '\n';
  file << "Radius: " << r << '\n';
  file << "Iterations: " << Iterations << '\n';
  file << "Time step: " << dt << '\n';
  file << "########################" << '\n';
  file.close();
}

void show_progress(long int start_time, double progress) {

  long int current_time, total_time;

  int current_time_min;
  int current_time_sec;
  int current_time_h;

  int total_time_min;
  int total_time_sec;
  int total_time_h;

  std::cout << "\033[2A";
  std::cout << "Progress: " << progress*100 << '%' << "             \n";

  current_time = time(NULL) - start_time;
  total_time = current_time * ((long int) 1/progress);
  if (total_time < 60) {
    cout << "Time: " << current_time << "s/" << total_time << "s";
  }
  else if (total_time < 3600) {
    total_time_sec = total_time % 60;
    total_time_min = total_time / 60;

    current_time_sec = current_time % 60;
    current_time_min = current_time / 60;

    cout << "Time: ";
    cout << current_time_min << "min " ;
    cout << current_time_sec << "s / ";
    cout << total_time_min << "min " ;
    cout << total_time_sec << "s";
  }
  else {
    total_time_sec = total_time % 60;
    total_time_min = (total_time % 3600) / 60;
    total_time_h = total_time / 3600;

    current_time_sec = current_time % 60;
    current_time_min = (current_time % 3600) / 60;
    current_time_h = current_time / 3600;

    cout << "Time: ";
    cout << current_time_h << "h ";
    cout << current_time_min << "min " ;
    cout << current_time_sec << "s / ";
    cout << total_time_h << "h ";
    cout << total_time_min << "min " ;
    cout << total_time_sec << "s";
  }
  cout << "                          \n";

}


int main(int argc, char const *argv[]) {
  long int start_time = time(NULL);

  double progress;

  srand(time(NULL));

  argparse(argc, argv);

  write_input();
  write_input(dir_path + input_filename);

  Vector3d box = {L,L,L};

  System particle_system(N,
    box,
    vel,
    r,
    &force,
    &potential);

  vector<double> EK;
  vector<double> EP;
  vector<double> t;
  vector<double> Energy_distribution_EK, Energy_distribution_EP;
  vector<vector<Vector3d>> particle_positions;



  for(int i = 0; i < Iterations; i++) {
    particle_system.update_system();

    if(display_progress and i%print_freq == 0 and i > 0) {
      progress = (float) i/(float)Iterations;
      show_progress(start_time, progress);
    }

    if(i%save_freq == 0) {
      particle_system.calc_kinetic();
      particle_system.calc_potential();

      EK.push_back(particle_system.get_kinetic()/(double) N);
      EP.push_back(particle_system.get_potential()/(double) N);


      particle_positions.push_back(particle_system.get_particle_positions());

      t.push_back(particle_system.get_time());
    }

  }

  ofstream energy_file (dir_path + energy_filename);
  ofstream position_file (dir_path + pos_filename);

  Energy_distribution_EK = particle_system.get_kinetic_distribution();
  Energy_distribution_EP = particle_system.get_potential_distribution();

  for (double val : EK) {
    energy_file << val << '\t';
  }
  energy_file << '\n';

  for (double val : EP) {
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

  for (double val : Energy_distribution_EK) {
    energy_file << val << '\t';
  }
  energy_file << '\n';

  for (double val : Energy_distribution_EP) {
    energy_file << val << '\t';
  }
  energy_file << '\n';

  energy_file.close();
  position_file.close();




  return 0;
}
