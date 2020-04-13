#include "UnitQuad.h"

UnitQuad::UnitQuad() : lightPos_(0.5f, 0.5f, -2.0f), sign_(1.0f)
{}

UnitQuad::~UnitQuad()
{}

void UnitQuad::init(const QString& textureFile)
{
	// The unit quad goes from 0.0 to 1.0 in each dimension.
	QVector<QVector3D> pos;
	QVector<QVector3D> norm;
	QVector<QVector2D> texCoord;
	QVector<unsigned int> idx;
    // unit positions.
    pos << QVector3D(0.0, 0.0, 0.0);
    pos << QVector3D(1.0, 0.0, 0.0);
    pos << QVector3D(0.0, 1.0, 0.0);
    pos << QVector3D(1.0, 1.0, 0.0);
    // We use normals for shading and lighting
    norm << QVector3D(0.0, 0.0, 1.0);
    norm << QVector3D(0.0, 0.0, 1.0);
    norm << QVector3D(0.0, 0.0, 1.0);
    norm << QVector3D(0.0, 0.0, 1.0);
    // Add in the texcoords
    texCoord << QVector2D(0.0, 0.0);
    texCoord << QVector2D(1.0, 0.0);
    texCoord << QVector2D(0.0, 1.0);
    texCoord << QVector2D(1.0, 1.0);
    idx << 0 << 1 << 2 << 2 << 1 << 3;
    Renderable::init(pos, norm, texCoord, idx, textureFile);
}

void UnitQuad::update(const qint64 msSinceLastFrame)
{
    // This is where we want to maintain our light.
    float secs = (float)msSinceLastFrame / 1000.0f;
    float angle = secs * 180.0f;
    // Rotate our light around the scene
    QMatrix4x4 rot;
    rot.setToIdentity();
    rot.rotate(angle, 0.0, 1.0, 0.0);
    QVector3D newPos = rot * lightPos_;
    lightPos_ = newPos;
    // Because we aren't doing any occlusion, the lighting on the walls looks
    // super wonky.  Instead, just move the light on the z axis.
    newPos.setX(0.5);
    shader_.bind();

    for(int i = 0; i < 3; i++) {
		std::string prefix = "pointLights[";
		prefix += std::to_string(i);
		prefix += "]";

		// each light should rotate differently so we can see them all.
		QMatrix4x4 newRot;
		newRot.setToIdentity();
		for(int j = 0; j < i; j++) {
		    newRot*=rot;
		}

        shader_.setUniformValue((prefix+".color").c_str(), 1.0f*i/3, 1.0f*(i+1)/3, 1.0f*(i+2)/3);
        shader_.setUniformValue((prefix+".position").c_str(), newRot*lightPos_);
        shader_.setUniformValue((prefix+".ambientIntensity").c_str(), 0.5f);
        shader_.setUniformValue((prefix+".specularStrength").c_str(), 0.5f);
        shader_.setUniformValue((prefix+".constant").c_str(), 1.0f);
        shader_.setUniformValue((prefix+".linear").c_str(), 0.09f);
        shader_.setUniformValue((prefix+".quadratic").c_str(), 0.032f);
	}

    shader_.release();
}
