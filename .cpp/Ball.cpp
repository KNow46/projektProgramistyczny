#pragma once
#include "Ball.h"
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <vector>


Ball::Ball(int x, int y, int height, int width, float speedX, float speedY, std::string animationPath, int framesCount)
    : GameObject(x, y, height, width, "res/textures/empty.png"), speedX(speedX), speedY(speedY), baseSpeedX(speedX), baseSpeedY(speedY),
    framesCounter(-1), framesCount(framesCount), frames(std::vector<Texture*>()), owner(player)
{
    speed = sqrt(speedX * speedX + speedY * speedY);
    double tg = speedY / speedX;
    for (int i = 0; i < framesCount; i++)
    {
        std::string filename = animationPath + "/frame" + std::to_string(i + 1) + ".png";
        Texture* bgFrame = new Texture(filename);
        frames.push_back(bgFrame);
    }
   
}

Ball::Ball(int x, int y, int height, int width, float speedX, float speedY, std::string texturePath, std::string enemyTexturePath)
    : GameObject(x, y, height, width, texturePath), speedX(speedX), speedY(speedY), baseSpeedX(speedX), baseSpeedY(speedY),
    framesCounter(-1), framesCount(0), frames(std::vector<Texture*>()), owner(player)
{
    speed = sqrt(speedX * speedX + speedY * speedY);
    double tg = speedY / speedX;
    for (int i = 0; i < framesCount; i++)
    {
        std::string filename = animationPath + "/frame" + std::to_string(i + 1) + ".png";
        Texture* bgFrame = new Texture(filename);
        frames.push_back(bgFrame);
    }
    enemyTexture = new Texture(enemyTexturePath);
}

const Texture* Ball::getTexture()
{
    if(framesCount > 0)
    {
        if (framesCounter >= 4 * (framesCount - 1))
            framesCounter = 0;
        framesCounter++;
        return frames[framesCounter / 4];
    }
    else if(owner == Owner::player)
    {
        return texture;
    }
    else if (owner == Owner::enemy)
    {
        return enemyTexture;
    }
}

void Ball::rotate()
{
    double xSpeedTmp = speedX;
    speedX = speedX * cos(angle * M_PI / 180.0) - speedY * sin(angle * M_PI / 180.0);
    speedY = xSpeedTmp * sin(angle * M_PI / 180.0) + speedY * cos(angle * M_PI / 180.0);

    if (abs(speedY) < 0.5 * abs(baseSpeedY))
    {
        if (speedY < 0)
        {
            speedY = -0.5 * abs(baseSpeedY);
        }
        else
        {
            speedY = 0.5 * abs(baseSpeedY);
        }
    }

    angle *= 0.99;
}

void Ball::move()
{
    x += speedX;
    y += speedY;
    rotate();
    if (y > windowHeight + 100)
    {
        isDestroyed = true;
    }
}

void Ball::setSpeedX(double x)
{
    this->speedX = x;
}

void Ball::setSpeedY(double y)
{
    this->speedY = y;
}

void Ball::setAngle(double x)
{
    angle = x;
}

float Ball::getSpeedY()
{
    return speedY;
}

float Ball::getSpeedX()
{
    return speedX;
}

float Ball::getBaseXSpeed()
{
    return baseSpeedX;
}

float Ball::getBaseYSpeed()
{
    return baseSpeedY;
}

Owner Ball::getOwner()
{
    return owner;
}

void Ball::setOwner(Owner owner)
{
    this->owner = owner;
}

void Ball::ballCollisionEffect()
{
}

void Ball::horizontalReflection()
{
    if (speedX > 0)
        speedX = -abs(baseSpeedX);
    else
        speedX = abs(baseSpeedX);

    angle = -angle;

}

void Ball::verticalReflection()
{
    if (speedY < 0)
        speedY = abs(baseSpeedY);
    else
        speedY = -abs(baseSpeedY);
    angle = -angle;

}

Ball::~Ball()
{
    int size = frames.size();
    for (int i = 0; i < size; i++)
    {
        delete frames[i];
    }
    delete enemyTexture;
}


