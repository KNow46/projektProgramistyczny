#include "StartButton.h"

bool StartButton::gameIsStarted = false;

StartButton::StartButton(int x, int y, int height, int width, std::string texturePath, std::string textureHoveredPath, std::vector<InterfaceObject*>& allInterfaceObjects, LevelGenerator& levelGenerator)
    : InterfaceObject(x, y, height, width, texturePath, textureHoveredPath), allInterfaceObjects(allInterfaceObjects), levelGenerator(levelGenerator)
{
}

void StartButton::onClick()
{
    gameIsStarted = true;

    while (!allInterfaceObjects.empty())
    {
        if (allInterfaceObjects.back() != this)
        {
            delete allInterfaceObjects.back();
        }
        allInterfaceObjects.pop_back();
    }

    Text* points = new Text(750, 43, 150, 30, "0", 15, Text::points);
    pointsPtr = points;
    allInterfaceObjects.push_back(points);

    Text* minimumPoints = new Text(810, 43, 150, 30, "/" + std::to_string(levelGenerator.getMinimumWinScore(1) ), 15, Text::requiredPoints);
    allInterfaceObjects.push_back(minimumPoints);

    levelGenerator.setPointsPtr(pointsPtr);
    levelGenerator.generate();
    delete this;
}

Text* StartButton::getPointsPtr()
{
    return pointsPtr;
}

bool StartButton::isGameStarted()
{
    return gameIsStarted;
}
void StartButton::setIsGameStarted(bool x)
{
    gameIsStarted = x;
}
