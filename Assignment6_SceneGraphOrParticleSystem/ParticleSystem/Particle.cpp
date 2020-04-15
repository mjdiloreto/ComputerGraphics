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

	msLeftToLive_ = lifespan;
}

void Particle::updateAndDraw(unsigned int msSinceLastFrame) {
	float elapsed = (float) msSinceLastFrame / 1000.0;
	float changeInVelocity = -9.8*elapsed;

	velocity_[1] += changeInVelocity;

//	qDebug() << "velocity";
//	qDebug() << velocity_;
//	qDebug() << "change in velocity";
//	qDebug() << changeInVelocity;
    QMatrix4x4 movement;
    movement.setToIdentity();
    movement.translate(velocity_/100);
    particleTransform_ *= movement;
	modelToRender_->setModelMatrix(particleTransform_);
    modelToRender_->draw(camera_->getViewMatrix(), camera_->getProjectionMatrix());

    msLeftToLive_ -= msSinceLastFrame;
}
