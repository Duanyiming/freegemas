#ifndef _PARTICULAS_H_
#define _PARTICULAS_H_

#include <Gosu/Gosu.hpp>

#include "Animation.h"
#include "log.h"
#include "Util.h"

#include <ctime>
#include <vector>
#include <cmath>

#define lim 0.70

namespace Gosu {
    class Window;
}

struct Particle{

    Particle(float angle, float distance, float size, int totalSteps, Gosu::Image img, Gosu::Color color) :
        mAngle(angle), mDistance(distance), mSize(size), mTotalSteps(totalSteps), mImage(img), mColor(color), mCurrentStep(0), mPosX(0), mPosY(0)
    { }

    void update() {
        if (mCurrentStep != mTotalSteps) {
            mCurrentStep ++;
        }

        float tempPos = Animacion::easeOutQuart(mCurrentStep, 0, 1, mTotalSteps);

        if (tempPos >= lim) {
            mColor.setAlpha(255 * (1 - (tempPos - lim) / (1 - lim)));
        } else {
            mColor.setAlpha(255);
        }

        mSizeCoef = mSize * (1 - tempPos);

        mPosX = tempPos * mDistance * std::cos(mAngle * 3.141592 / 180) - mImage.width() * mSizeCoef / 2;
        mPosY = tempPos * mDistance * std::sin(mAngle * 3.141592 / 180) - mImage.height() * mSizeCoef / 2;


    }

    void draw(int oX, int oY){
        mImage.draw(oX + mPosX, oY + mPosY, 7, mSizeCoef, mSizeCoef, mColor);
    }

    float estado(){
        return (float)mCurrentStep / (float)mTotalSteps;
    }


    float mAngle;

    float mDistance;

    float mSize;

    int mTotalSteps;

    Gosu::Image mImage;

    Gosu::Color mColor;

    int mCurrentStep;

    float mPosX;

    float mPosY;

    float mSizeCoef;
};


class ParticleSystem{

public:
    ParticleSystem(Gosu::Window * parentWindow,
                      unsigned particleQuantity,
                      unsigned totalSteps,
                      int x,
                      int y,
                      unsigned distance=200,
                      float scale=1,
                      Gosu::Color color = Gosu::Color::WHITE) :

        mParticleQuantity(particleQuantity),
        mTotalSteps(totalSteps),
        mCurrentStep(0),
        mDistance(distance),
        mScale(scale),
        mColor(color),
        mPosX(x),
        mPosY(y),
        mActive(true),
        // Load the images for the particles
        mImgParticle1(L"media/partc1.png"),
        mImgParticle2(L"media/partc2.png")
    {
        // Reserve the space for the particles
        mParticleVector.reserve(mParticleQuantity);

        // Create the particles
        for (size_t i = 0; i < mParticleQuantity; ++i)
        {
            mParticleVector.push_back(Particle(getRandomInt(0, 360),
                                    getRandomFloat(0, 1) * mDistance,
                                    getRandomFloat(0, mScale) + 1,
                                    getRandomFloat(0.1, 1) * mTotalSteps,
                                    (rand() > RAND_MAX / 2 ? mImgParticle1 : mImgParticle2),
                                    mColor));
        }

    }

    bool ended(){
        return !mActive;
    }

    void draw(){

        if (++mCurrentStep < mTotalSteps){
            for (unsigned i = 0; i < mParticleQuantity; ++i){
                mParticleVector[i].update();
                mParticleVector[i].draw(mPosX, mPosY);
            }
        } else {
            mActive = false;
        }
    }

private:

    unsigned mParticleQuantity;

    /// Duración del efecto
    float mTotalSteps;

    /// Posición de la animación
    float mCurrentStep;

    /// Distancia del efecto
    float mDistance;

    /// Escala de la explosión
    float mScale;

    /// Color de las partículas
    Gosu::Color mColor;

    /// Imágenes de las partículas
    Gosu::Image mImgParticle1, mImgParticle2;

    /// Contenedor para las partículas
    vector<Particle> mParticleVector;

    /// Posición donde se debe pintar
    int mPosX, mPosY;

    /// Flag que indica si el sistema de partícula está activo
    bool mActive;

};

#endif /* _PARTICULAS_H_ */
