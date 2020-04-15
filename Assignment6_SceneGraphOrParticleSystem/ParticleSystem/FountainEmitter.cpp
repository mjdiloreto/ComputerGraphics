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
	// remove dead particles
	int removedParticles = 0;
    for(auto p: particles_) {
    	if (p->isDead()) {
    		p->reset(position_, makeParticleVelocity(), TIME_TO_LIVE);
    		removedParticles++;
		}
    }
	
	// add new particles
	int particlesToAdd = (msSinceLastFrame / 1000) - removedParticles;
	for(int i = 0; i < particlesToAdd; i++) {
		Particle* newP = new Particle(particleModel_, camera_, position_, makeParticleVelocity(), TIME_TO_LIVE);
		this->particles_.append(newP);
	}

	// update all particles
    for (auto p: particles_) {
    	p->updateAndDraw(msSinceLastFrame);
	}
}

