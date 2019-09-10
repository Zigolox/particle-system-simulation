#include "particle.h"
void Particle::update(double dt){
  /*Update position and velocity using timestep t and velocity verlet*/
  vel += vel*dt + 0.5*(acc + acc_prev)*dt; //Update the velocity
  pos += vel*dt + 0.5*acc*dt*dt; //Update the position
  acc_prev = acc;  //Update the previous acceleration

  //Set current accleration to 0
  acc[0] = 0;
  acc[1] = 0;
  acc[2] = 0;

  //Update energy
  kinetic_energy = 0.5*mass* norm(vel);

}
