#pragma once

#include "InterfaceObject.h"
#include <vector>
#include "Texture.h"
#include "Rocket.h"
#include "Ball.h"
#include "Block.h"
#include "BackGround.h"
#include "Text.h"

class LevelGenerator
{
public:
    LevelGenerator(std::vector<GameObject*>& allSceneObjects, std::vector<InterfaceObject*>& allInterfaceObjects);

    void setPointsPtr(Text* ptr);
    void setCurrentLevel(int level);
    void generate();
    void increaseLevel();
    int getCurrentLevel();
    static int getMinimumWinScore(int level);

protected:
    std::vector<GameObject*>& allSceneObjects;
    std::vector<InterfaceObject*>& allInterfaceObjects;
    Text* pointsPtr;
    int currentLevel;
};
