#ifndef PARTICLE
#define PARTICLE
#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <armadillo>
#define PI 3.14159265358979323846
using namespace std;
using namespace arma;

class Particle {
private:
  arma::vec pos; //Position of particle
  arma::vec vel; //Velocity of particle
  arma::vec2 rot; //Orientation of particle, will probably not be used

  arma::vec acc_prev;  //Previous acceleration
  arma::vec acc;       //Current acceleration

  double mass;    //Mass of particle
  double kinetic_energy;
  double radius;
public:
  Particle(arma::vec box_dimensions, double start_velocity){
    /*Initializer for particle class. Takes average velocity and
    box dimensions, i.e. interval for the x,y,z, coordinates as input*/

    //Set the position of the particle to a random coordinate in the box
    double x,y,z;
    x = (double) rand()/(double) RAND_MAX * box_dimensions[0];
    y = (double) rand()/(double) RAND_MAX * box_dimensions[1];
    z = (double) rand()/(double) RAND_MAX * box_dimensions[2];
    pos = {x,y,z};

    //Set the velocity in some random direction
    double theta, phi;
    theta = (double) rand()/(double) RAND_MAX * 2 * PI;
    phi = (double) rand()/(double) RAND_MAX * PI;
    vel = {start_velocity*sin(theta)*cos(phi),
      start_velocity*cos(theta)*cos(phi),
      start_velocity*cos(phi)};

    //Set the radius of the particle to 0
    radius = 0;

    //Set the mass of the particle to one
    mass = 1;

    //Set the acceleration of the particle to 0
    acc = {0,0,0};
    acc_prev = {0,0,0};
  }

  Particle(arma::vec box_dimensions, double start_velocity, double r){
    /*Initializer for particle class. Takes average velocity and
    box dimensions, i.e. interval for the x,y,z, coordinates as input*/

    //Set the position of the particle to a random coordinate in the box
    double x,y,z;
    x = (double) rand()/(double) RAND_MAX * box_dimensions[0];
    y = (double) rand()/(double) RAND_MAX * box_dimensions[1];
    z = (double) rand()/(double) RAND_MAX * box_dimensions[2];
    pos = {x,y,z};

    //Set the velocity in some random direction
    double theta, phi;
    theta = (double) rand()/(double) RAND_MAX * 2 * PI;
    phi = (double) rand()/(double) RAND_MAX * PI;
    vel = {start_velocity*sin(theta)*cos(phi),
      start_velocity*cos(theta)*cos(phi),
      start_velocity*cos(phi)};

    //Set the radius of the particle
    radius = r;

    //Set the mass of the particle to one
    mass = 1;

    //Set the acceleration of the particle to 0
    acc = {0,0,0};
    acc_prev = {0,0,0};
  }

  Particle(arma::vec box_dimensions, double start_velocity,double r, double m){
    /*Initializer for particle class. Takes average velocity and
    box dimensions, i.e. interval for the x,y,z, coordinates as input.
    This initalizer also takes the mass of the particle as input.*/

    //Set the position of the particle to a random coordinate in the box
    double x,y,z;
    x = (double) rand()/(double) RAND_MAX * box_dimensions[0];
    y = (double) rand()/(double) RAND_MAX * box_dimensions[1];
    z = (double) rand()/(double) RAND_MAX * box_dimensions[2];
    pos = {x,y,z};

    //Set the velocity in some random direction
    double theta, phi;
    theta = (double) rand()/(double) RAND_MAX * 2 * PI;
    phi = (double) rand()/(double) RAND_MAX * PI;
    vel = {start_velocity*sin(theta)*cos(phi),
      start_velocity*cos(theta)*cos(phi),
      start_velocity*cos(phi)};

    //Set the radius of the particle
    radius = r;

    //Set the mass of the particle
    mass = m;

    //Set the acceleration of the particle to 0
    acc = {0,0,0};
    acc_prev = {0,0,0};
  }

  void addForce(arma::vec F){acc = acc + F*(1/mass);}

  arma::vec get_position(){return pos;}

  arma::vec get_velocity(){return vel;}

  double get_mass(){return mass;}

  double get_radius(){return radius;}

  double get_energy(){return kinetic_energy;}

  void print_data(){
    /*Print all data for one particle. This function is used in testing.*/
    std::cout << "Position: (" << pos[0] << ", " << pos[1] << ", "
    << pos[2] << ")" << '\n';
    std::cout << "Velocity: (" << vel[0] << ", " << vel[1] << ", "
    << vel[2] << ")" << '\n';
    std::cout << "Mass: " << mass << '\n';
  }

  void collide(arma::vec dr, arma::vec dv){
    /*Function to call if two particles collide*/
    pos = pos + dr;
    vel = vel + dv;





  }

  void update(double dt);

};
#endif
