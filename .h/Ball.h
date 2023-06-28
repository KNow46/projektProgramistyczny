#pragma once
#include "GameObject.h"
#include <string>
#include <vector>
#include "Global.h"

class Ball : public GameObject
{
public:
    Ball(int x, int y, int height, int width, float speedX, float speedY, std::string animationPath, int framesCount);
    Ball(int x, int y, int height, int width, float speedX, float speedY, std::string texturePlayerPath, std::string enemyTexturePath);

    ~Ball();

    void move();

    void rotate();

    void ballCollisionEffect();

    void horizontalReflection();

    void verticalReflection();

    const Texture* getTexture();

    void setSpeedX(double x);

    void setSpeedY(double y);

    void setAngle(double x);

    float getSpeedY();

    float getSpeedX();

    float getBaseXSpeed();

    float getBaseYSpeed();

    Owner getOwner();

    void setOwner(Owner);

private:
    double speedX;
    double speedY;
    double speed;
    double baseSpeedX;
    double baseSpeedY;
    double baseSpeed;
    double angle;
    int framesCounter;
    int framesCount;
    std::string animationPath;
    std::vector<Texture*> frames;
    Owner owner;
    Texture* enemyTexture;
 
};
