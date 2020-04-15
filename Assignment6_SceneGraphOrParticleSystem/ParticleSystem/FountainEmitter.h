#pragma once
#include <QtOpenGL>
#include "Renderable.h"
#include "Particle.h"
#include "Camera.h"

// How long should particles last (ms)?
#define TIME_TO_LIVE 2000
#define SPREAD 50

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
  
public:
  FountainEmitter(Camera* camera, const QVector3D& position, const QVector3D& orientation, unsigned int pps, Renderable* particleModel);

  virtual ~FountainEmitter();

  void update(unsigned int msSinceLastFrame);   
};
