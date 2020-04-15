#pragma once
#include <QtOpenGL>
#include "Renderable.h"
#include "Camera.h"

class Particle {
protected:
  Renderable* modelToRender_;
  Camera* camera_;
  QMatrix4x4 particleTransform_;
  QVector3D velocity_;
  float secondsLeftToLive_;

public:
  Particle(Renderable* model, Camera* camera_, const QVector3D& position, const QVector3D& velocity, float lifespan);
  
  virtual ~Particle();

  void reset(const QVector3D& position, const QVector3D& velocity, float lifespan);

  void updateAndDraw(unsigned int msSinceLastFrame);
  bool isDead() const {return secondsLeftToLive_ > 0.0;}
};
