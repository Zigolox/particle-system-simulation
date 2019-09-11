#include "particle_system.h"

System::System(int amount_of_particles,
  Vector3d box_dimensions,
  double start_velocity){
  /*Initalizer for particle system class. Set amount of particles N,
  box dimensions, and start velocity for the particles.*/
  box = box_dimensions;

  //Create all particles
  for (int i = 0; i < N; i++) {
      particles.push_back(new Particle(box_dimensions, start_velocity));
  }

  //Save the amount of particles
  N = amount_of_particles;
}

void System::wall_collision(int i){
  /*Check if particle i has collided with a wall*/

  Vector3d pos = particles[i] -> get_position();
  Vector3d vel = particles[i] -> get_velocity();
  Vector3d dr = {0,0,0};
  Vector3d dv = {0,0,0};


  //Check if the particle is inside the box for each coordinate
  for(int j = 0; j < 3; j++){
    if(pos[j] < 0){
      dr[j] = - pos[j];
      dv[j] = - 2*vel[j];
    }
    if(pos[j] > box[j]){
      dr[j] = - (pos[j] - box[j]);
      dv[j] = - 2*vel[j];
    }
  }
  particles[i] -> collide(dr, dv);
}

bool System::collision_check(int i, int j){
  /*Check if particles i and j have collided*/
  Vector3d pos1, pos2;
  double r1, r2, dis;

  pos1 = particles[i] -> get_position();
  pos2 = particles[j] -> get_position();
  r1 = particles[i] -> get_radius();
  r2 = particles[j] -> get_radius();

  dis = (pos2 - pos1).norm();

  return dis <(r1 + r2);
}
