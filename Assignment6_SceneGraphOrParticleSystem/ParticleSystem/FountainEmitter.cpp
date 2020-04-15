#include "FountainEmitter.h"

FountainEmitter::~FountainEmitter() {
    for(auto p : particles_) {
        delete p;
	}
}

FountainEmitter::FountainEmitter(Camera* camera, const QVector3D& position, const QVector3D& orientation, unsigned int pps, Renderable* particleModel): camera_(camera), position_(position), orientation_(orientation), particlesPerSecond_(pps), particleModel_(particleModel) {
}

void FountainEmitter::update(unsigned int msSinceLastFrame) {
	timeLivedSoFar += msSinceLastFrame;
	particleModel_->update(msSinceLastFrame);
	// remove dead particles
    for(auto p: particles_) {
    	if (p->isDead()) {
    		p->reset(position_, makeParticleVelocity(), TIME_TO_LIVE);
    		lastEmittedAt = timeLivedSoFar;
		}
    }
	
	// add new particle
	float particlesRate = 1000.0 / particlesPerSecond_;
	int particlesToAdd = (timeLivedSoFar - lastEmittedAt) / particlesRate;
	for(int i = 0; i < particlesToAdd; i++) {
		if (i == 0) lastEmittedAt = timeLivedSoFar;
		Particle* newP = new Particle(particleModel_, camera_, position_, makeParticleVelocity(), TIME_TO_LIVE);
		this->particles_.append(newP);
	}

    for (auto p: particles_) {
    	p->updateAndDraw(msSinceLastFrame);
	}
}

