#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
#include "Global.h"


class Rocket : public GameObject
{
public:
    Rocket(int x, int y, int height, int width, std::string animationPath, int framesCount, Owner owner);

    void setSpeed(double x);

    const Texture* getTexture();

    double getSpeed();

    Owner getOwner();

    ~Rocket();

private:
    double speed;
    int framesCounter;
    int framesCount;
    std::string animationPath;
    std::vector<Texture*> frames;
    Owner rocketOwner;

    void ballCollisionEffect();
};




