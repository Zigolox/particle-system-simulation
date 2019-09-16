#include "particle_system.h"

System::System(int amount_of_particles,
  Vector3d box_dimensions,
  double start_velocity) {
  /*Initalizer for particle system class. Set amount of particles N,
  box dimensions, and start velocity for the particles.*/
  box = box_dimensions;

  //Save the amount of particles
  N = amount_of_particles;

  //Create all particles
  for (int i = 0; i < N; i++) {
      particles.push_back(new Particle(box_dimensions, start_velocity));
  }



}

System::System(int amount_of_particles,
  Vector3d box_dimensions,
  double start_velocity,
  Vector3d (*force)(Particle *p1, Particle *p2)) {
  /*Initalizer for particle system class. Set amount of particles N,
  box dimensions, and start velocity for the particles.*/
  box = box_dimensions;

  //Save the amount of particles
  N = amount_of_particles;

  //Create all particles
  for (int i = 0; i < N; i++) {
      particles.push_back(new Particle(box_dimensions, start_velocity));
  }

  force_function = force;


}

System::System(int amount_of_particles,
  Vector3d box_dimensions,
  double start_velocity,
  Vector3d (*force)(Particle *p1, Particle *p2),
  double (*potential)(Particle *p1, Particle *p2)) {
  /*Initalizer for particle system class. Set amount of particles N,
  box dimensions, and start velocity for the particles.*/
  box = box_dimensions;

  //Save the amount of particles
  N = amount_of_particles;

  //Create all particles
  for (int i = 0; i < N; i++) {
      particles.push_back(new Particle(box_dimensions, start_velocity));
  }

  force_function = force;
  potential_function = potential;

}

System::System(int amount_of_particles,
  Vector3d box_dimensions,
  double r,
  double start_velocity) {
  /*Initalizer for particle system class. Set amount of particles N,
  box dimensions, and start velocity for the particles.*/
  box = box_dimensions;

  //Save the amount of particles
  N = amount_of_particles;

  //Create all particles
  for (int i = 0; i < N; i++) {
      particles.push_back(new Particle(box_dimensions, start_velocity, r));
  }


}

System::System(int amount_of_particles,
  Vector3d box_dimensions,
  double start_velocity,
  double r,
  Vector3d (*force)(Particle *p1, Particle *p2)) {
  /*Initalizer for particle system class. Set amount of particles N,
  box dimensions, and start velocity for the particles.*/
  box = box_dimensions;

  //Save the amount of particles
  N = amount_of_particles;

  //Create all particles
  for (int i = 0; i < N; i++) {
      particles.push_back(new Particle(box_dimensions, start_velocity, r));
  }



  force_function = force;


}

System::System(int amount_of_particles,
  Vector3d box_dimensions,
  double start_velocity,
  double r,
  Vector3d (*force)(Particle *p1, Particle *p2),
  double (*potential)(Particle *p1, Particle *p2)) {
  /*Initalizer for particle system class. Set amount of particles N,
  box dimensions, and start velocity for the particles.*/
  box = box_dimensions;

  //Save the amount of particles
  N = amount_of_particles;

  //Create all particles
  for (int i = 0; i < N; i++) {
      particles.push_back(new Particle(box_dimensions, start_velocity, r));
  }


  force_function = force;
  potential_function = potential;

}


void System::wall_collision(int i) {
  /*Check if particle i has collided with a wall*/
  Particle *p = particles[i];

  Vector3d pos = p -> get_position();
  Vector3d vel = p -> get_velocity();
  Vector3d dr = {0,0,0};
  Vector3d dv = {0,0,0};


  //Check if the particle is inside the box for each coordinate
  for(int j = 0; j < 3; j++) {
    if(pos[j] < 0) {
      dr[j] = - pos[j];
      dv[j] = - 2*vel[j];
    }
    if(pos[j] > box[j]) {
      dr[j] = - (pos[j] - box[j]);
      dv[j] = - 2*vel[j];
    }
  }
  p -> collide(dr, dv);
}

bool System::collision_check(int i, int j) {
  /*Check if particles i and j have collided*/
  Vector3d pos1, pos2;
  double r1, r2, dis;
  Particle *p1, *p2;

  p1 = particles[i];
  p2 = particles[j];


  pos1 = p1 -> get_position();
  pos2 = p2 -> get_position();
  r1 = p1 -> get_radius();
  r2 = p2 -> get_radius();

  dis = (pos2 - pos1).norm();

  return dis < (r1 + r2);
}

void System::collision(int i, int j) {
  /*Set new velocities and positions after a collision between
  particles i and j. Position of center of mass is constant,*/
  Particle *p1, *p2;
  Vector3d pos1, pos2, pos_COM , pos_rel, dpos1, dpos2;
  Vector3d vel1, vel2, vel_COM, vel1_rel, vel2_rel, dvel1, dvel2;
  double m1, m2;
  double r1, r2, dis, dis0;

  p1 = particles[i];
  p2 = particles[j];

  pos1 = p1 -> get_position();
  pos2 = p2 -> get_position();
  vel1 = p1 -> get_velocity();
  vel2 = p2 -> get_velocity();
  r1 = p1 -> get_radius();
  r2 = p2 -> get_radius();
  m1 = p1 -> get_mass();
  m2 = p2 -> get_mass();

  vel_COM = (m1*vel1 + m2*vel2)/(m1 + m2);
  vel1_rel = vel1 - vel_COM;
  vel2_rel = vel2 - vel_COM;

  pos_rel = pos2 - pos1;

  dvel1 = -2*vel1_rel.dot(pos_rel)/pos_rel.dot(pos_rel)*pos_rel;
  dvel2 = -dvel1*m2/m1;

  dis = pos_rel.norm();
  dis0 = r1 + r2;

  dpos1 = -m2*(dis0-dis)/((m1 + m2)*dis)*pos_rel;
  dpos2 =-m1/m2*dpos1;

  p1 -> collide(dpos1,dvel1);
  p2 -> collide(dpos2, dvel2);

}

void System::update_system() {

  for(int i = 0; i < N; i++) {
    //Update all particles
    particles[i] -> update(dt);

    //Check wall collisions
    wall_collision(i);
  }

  Vector3d F;
  for(int i = 0; i < N-1; i++) {
    for(int j = i + 1; j < N; j++) {
      //Check particle collisions
      if(collision_check(i,j)) {
        collision(i,j);
      }

      //Add particle forces
      F = (*force_function)(particles[i], particles[j]);
      particles[i] -> add_force(F);
      particles[j] -> add_force(-F);
    }
  }

  t += dt;
}

void System::calc_kinetic() {
  kinetic_energy = 0;
  for(int i = 0; i < N; i++) {
    //std::cout << "Energy " << i <<": "<< particles[i] -> get_energy() << '\n';
    kinetic_energy += particles[i] -> get_energy();
  }
}

vector<double> System::get_kinetic_distribution() {
  /*Get kinetic energy distribution*/

  vector<double> distribution;
  for(int i = 0; i < N; i++) {
    distribution.push_back(particles[i] -> get_energy());
  }

  /*Not optimized but it does not matter*/
  sort(distribution.begin(), distribution.end());

  return distribution;
}

void System::calc_potential() {
  potential_energy = 0;
  for(int i = 0; i < N - 1; i++) {
    for(int j = i +1; j < N; j++) {
      potential_energy += (*potential_function)(particles[i], particles[j]);
    }
  }
}

vector<double> System::get_potential_distribution() {
  /*Get kinetic energy distribution*/

  vector<double> distribution;

  for(int i = 0; i < N - 1; i++) {
    for(int j = i + 1; j < N; j++) {
      distribution.push_back((*potential_function)(particles[i], particles[j]));
    }
  }

  /*Not optimized but it does not matter*/
  sort(distribution.begin(), distribution.end());

  return distribution;
}

vector<Vector3d> System::get_particle_positions() {
  /*Returns a vector containing the position of all particles*/
  vector<Vector3d> positions;

  for(Particle *p : particles) {
    positions.push_back(p -> get_position());
  }

  return positions;
}
