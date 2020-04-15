#include "Particle.h"

Particle::Particle(Renderable* model, Camera* camera, const QVector3D& position, const QVector3D& velocity, float lifespan): modelToRender_(model), camera_(camera) {
    reset(position, velocity, lifespan);
}

Particle::~Particle() {
}


void Particle::reset(const QVector3D& position, const QVector3D& velocity, float lifespan) {
	velocity_.setX(velocity.x());
	velocity_.setY(velocity.y());
	velocity_.setZ(velocity.z());
	
	particleTransform_.setToIdentity();
    particleTransform_.translate(position);

//	particleTransform_ = QMatrix4x4(
//		1,0,0,position.x(),
//		0,1,0,position.y(),
//		0,0,1,position.z(),
//		0,0,0,1);
	secondsLeftToLive_ = lifespan;
}

void Particle::updateAndDraw(unsigned int msSinceLastFrame) {
	//velocity_ *= -(9.8 * 9.8);
	// TODO apply gravity and velocity
	modelToRender_->setModelMatrix(particleTransform_);
    modelToRender_->draw(camera_->getViewMatrix(), camera_->getProjectionMatrix());
}
