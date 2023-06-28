#pragma once
#include "GameObject.h"
#include "Texture.h"
#include <string>
#include "Global.h"
#include <vector>
#include <sstream>
#include <forward_list>


class Background : public GameObject
{
public:
    Background(std::string animationPath, int framesCount);

    const Texture* getTexture();

    ~Background();

private:
    int framesCounter;
    int framesCount;
    std::string animationPath;
   std::vector<Texture*> frames;

    void ballCollisionEffect();
};