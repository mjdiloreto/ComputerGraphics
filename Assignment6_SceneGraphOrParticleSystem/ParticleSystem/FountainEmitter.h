#pragma once
#include <QtOpenGL>
#include "Renderable.h"
#include "Particle.h"
#include "Camera.h"
#include <random>

// How long should particles last (ms)?
#define TIME_TO_LIVE 3000
#define SPREAD 7
#define FORCE 7

// This Emitter emits particles in a relatively upward direction, and
// particles are then affected by gravity until they die
class FountainEmitter {
protected:
  Camera* camera_;
  QVector<Particle*> particles_;
  QVector3D position_;
  QVector3D orientation_;
  unsigned int particlesPerSecond_;
  Renderable* particleModel_;

  // we want to emit one right at the beginning.
  long lastEmittedAt = -1000;
  long timeLivedSoFar = 0;
  
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::normal_distribution<> d{0, 0.12};
  float iota() {return d(gen);}
  QVector3D makeParticleVelocity() {
	// go up little boy.
	return QVector3D(iota()*SPREAD,FORCE+iota()*SPREAD,iota()*SPREAD);
  }
  
public:
  FountainEmitter(Camera* camera, const QVector3D& position, const QVector3D& orientation, unsigned int pps, Renderable* particleModel);

  virtual ~FountainEmitter();

  void update(unsigned int msSinceLastFrame);   
};
