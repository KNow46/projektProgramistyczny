#include "LevelGenerator.h"
#include "RedBlock.h"
#include "YellowBlock.h"

LevelGenerator::LevelGenerator(std::vector<GameObject*>& allSceneObjects, std::vector<InterfaceObject*>& allInterfaceObjects) :
    allInterfaceObjects(allInterfaceObjects), allSceneObjects(allSceneObjects), currentLevel(1)
{
}

void LevelGenerator::setPointsPtr(Text* ptr)
{
    pointsPtr = ptr;
}

void LevelGenerator::setCurrentLevel(int level)
{
    currentLevel = level;
}

void LevelGenerator::generate()
{
    while (!allSceneObjects.empty())
    {
        delete allSceneObjects.back();
        allSceneObjects.pop_back();
    }

    if (currentLevel == 1)
    {
        allSceneObjects.push_back(new Background("res/textures/backgroundAnimation", 28));

        allSceneObjects.push_back(new Rocket(windowWidth / 2 + 60, windowHeight - 60, 140 * 1.5, 35 * 1.5, "res/textures/enemyRocketAnimation", 20, enemy));
        allSceneObjects.push_back(new Rocket(windowWidth / 2 + 60, windowHeight - 60, 140 * 1.5, 35 * 1.5, "res/textures/rocketAnimation", 20, player));

        allSceneObjects.push_back(new Ball(300, 450, 35 * 1.5, 35 * 1.5, -6 * 1.5, -6 * 1.5, "res/textures/playerBall.png", "res/textures/enemyBall.png"));

        for (int i = 0; i < 5; i++)
        {
            allSceneObjects.push_back(new Block(50 + i * 60 * 1.5, 200 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/block.png", pointsPtr));
        }
        allSceneObjects.push_back(new RedBlock(windowWidth / 2 + 30 * 1.5, 150 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/redBlock.png", pointsPtr));
    }
    else if (currentLevel == 2)
    {
        allSceneObjects.push_back(new Background("res/textures/backgroundAnimation", 28));

        allSceneObjects.push_back(new Rocket(windowWidth / 2 + 60, windowHeight - 60, 140 * 1.5, 35 * 1.5, "res/textures/enemyRocketAnimation", 20, enemy));
        allSceneObjects.push_back(new Rocket(windowWidth / 2 + 60, windowHeight - 60, 140 * 1.5, 35 * 1.5, "res/textures/rocketAnimation", 20, player));

        allSceneObjects.push_back(new Ball(300, 450, 35 * 1.5, 35 * 1.5, -6 * 1.5, -6 * 1.5, "res/textures/playerBall.png", "res/textures/enemyBall.png"));

        for (int i = 0; i < 9; i++)
        {
            allSceneObjects.push_back(new Block(50 + i * 60 * 1.5, 200 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/block.png", pointsPtr));
        }
    }
    else if (currentLevel == 3)
    {
        allSceneObjects.push_back(new Background("res/textures/backgroundAnimation", 28));

        allSceneObjects.push_back(new Rocket(windowWidth / 2 + 60, windowHeight - 60, 140 * 1.5, 35 * 1.5, "res/textures/enemyRocketAnimation", 20, enemy));
        allSceneObjects.push_back(new Rocket(windowWidth / 2 + 60, windowHeight - 60, 140 * 1.5, 35 * 1.5, "res/textures/rocketAnimation", 20, player));

        allSceneObjects.push_back(new Ball(300, 450, 35 * 1.5, 35 * 1.5, -6 * 1.5, -6 * 1.5, "res/textures/playerBall.png", "res/textures/enemyBall.png"));

        for (int i = 0; i < 9; i++)
        {
            allSceneObjects.push_back(new Block(50 + i * 60 * 1.5, 200 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/block.png", pointsPtr));
        }
        for (int i = 0; i < 9; i++)
        {
            allSceneObjects.push_back(new YellowBlock(50 + i * 60 * 1.5, 150 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/yellowBlock.png", pointsPtr));
        }
    }
    else if (currentLevel == 4)
    {
        allSceneObjects.push_back(new Background("res/textures/backgroundAnimation", 28));

        allSceneObjects.push_back(new Rocket(windowWidth / 2 + 60, windowHeight - 60, 140 * 1.5, 35 * 1.5, "res/textures/enemyRocketAnimation", 20, enemy));
        allSceneObjects.push_back(new Rocket(windowWidth / 2 + 60, windowHeight - 60, 140 * 1.5, 35 * 1.5, "res/textures/rocketAnimation", 20, player));

        allSceneObjects.push_back(new Ball(300, 450, 35 * 1.5, 35 * 1.5, -6 * 1.5, -6 * 1.5, "res/textures/playerBall.png", "res/textures/enemyBall.png"));

        for (int i = 0; i < 9; i++)
        {
            allSceneObjects.push_back(new Block(50 + i * 60 * 1.5, 200 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/block.png", pointsPtr));
        }
        for (int i = 0; i < 9; i++)
        {
            allSceneObjects.push_back(new Block(50 + i * 60 * 1.5, 100 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/block.png", pointsPtr));
        }
        for (int i = 0; i < 9; i++)
        {
            allSceneObjects.push_back(new Block(50 + i * 60 * 1.5, 150 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/block.png", pointsPtr));
        }
    }
    else if (currentLevel == 5)
    {
        allSceneObjects.push_back(new Background("res/textures/backgroundAnimation", 28));

        allSceneObjects.push_back(new Rocket(windowWidth / 2 + 60, windowHeight - 60, 140 * 1.5, 35 * 1.5, "res/textures/enemyRocketAnimation", 20, enemy));
        allSceneObjects.push_back(new Rocket(windowWidth / 2 + 60, windowHeight - 60, 140 * 1.5, 35 * 1.5, "res/textures/rocketAnimation", 20, player));

        allSceneObjects.push_back(new Ball(300, 450, 35 * 1.5, 35 * 1.5, -6 * 1.5, -6 * 1.5, "res/textures/playerBall.png", "res/textures/enemyBall.png"));

        for (int i = 0; i < 9; i++)
        {
            allSceneObjects.push_back(new Block(50 + i * 60 * 1.5, 200 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/block.png", pointsPtr));
        }
        for (int i = 0; i < 9; i++)
        {
            allSceneObjects.push_back(new Block(50 + i * 60 * 1.5, 150 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/block.png", pointsPtr));
        }
        for (int i = 0; i < 9; i++)
        {
            allSceneObjects.push_back(new RedBlock(50 + i * 60 * 1.5, 100 * 1.5, 60 * 1.5, 30 * 1.5, "res/textures/redBlock.png", pointsPtr));
        }
    }
    else if (currentLevel > 5)
    {
        allSceneObjects.push_back(new Block(0, 0, windowWidth, windowHeight, "res/textures/winScreen.png", pointsPtr));
    }
}

void LevelGenerator::increaseLevel()
{
    currentLevel++;
}

int LevelGenerator::getCurrentLevel()
{
    return currentLevel;
}

int LevelGenerator::getMinimumWinScore(int level)
{
    if (level == 1)
    {
        return 100;
    }
    else if (level == 2)
    {
        return 330;
    }
    else if (level == 3)
    {
        return 900;
    }
    else if (level == 4)
    {
        return 1700;
    }
    else if (level == 5)
    {
        return 2500;
    }
    else if (level > 5)
    {
        return -1;
    }
}
