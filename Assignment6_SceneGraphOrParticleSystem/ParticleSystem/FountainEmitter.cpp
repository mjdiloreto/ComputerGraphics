#include "FountainEmitter.h"

QVector3D makeParticleVelocity() {
	// go up little boy.
	return QVector3D(0.0f,1.0f,0.0f);
}

FountainEmitter::~FountainEmitter() {
    for(auto p : particles_) {
        delete p;
	}
}

FountainEmitter::FountainEmitter(Camera* camera, const QVector3D& position, const QVector3D& orientation, unsigned int pps, Renderable* particleModel): camera_(camera), position_(position), orientation_(orientation), particlesPerSecond_(pps), particleModel_(particleModel) {
}

void FountainEmitter::update(unsigned int msSinceLastFrame) {
	qDebug() << "msSinceLastFrame " << msSinceLastFrame;
	particleModel_->update(msSinceLastFrame);
	// remove dead particles
	int removedParticles = 0;
    for(auto p: particles_) {
    	if (p->isDead()) {
	        qDebug() << "DEAD PARTICLE ";
    		p->reset(position_, makeParticleVelocity(), TIME_TO_LIVE);
    		removedParticles++;
		}
    }
	
	// add new particle
	timeLivedSoFar += msSinceLastFrame;
	int particlesRate = 1000.0 / particlesPerSecond_;
	int particlesToAdd = (timeLivedSoFar - lastEmittedAt) / particlesRate;
	for(int i = 0; i < particlesToAdd - removedParticles; i++) {
		if (i == 0) lastEmittedAt = timeLivedSoFar;
		Particle* newP = new Particle(particleModel_, camera_, position_, makeParticleVelocity(), TIME_TO_LIVE);
		this->particles_.append(newP);
	}

	qDebug() << "removedParticles " << removedParticles;
	qDebug() << "particlesToAdd " << particlesToAdd;
	qDebug() << "particles_.size() " << particles_.size();

	// update all particles
    for (auto p: particles_) {
    	p->updateAndDraw(msSinceLastFrame);
	}
}

