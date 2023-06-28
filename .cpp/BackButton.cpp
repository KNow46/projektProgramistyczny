#include "BackButton.h"
#include "StartButton.h"
#include "HighScoresButton.h"
#include "Text.h"

BackButton::BackButton(int x, int y, int height, int width, std::string texturePath, std::string textureHoveredPath, std::vector<InterfaceObject*>& allInterfaceObjects, LevelGenerator& levelGenerator)
    : InterfaceObject(x, y, height, width, texturePath, textureHoveredPath), allInterfaceObjects(allInterfaceObjects), levelGenerator(levelGenerator) {}

void BackButton::onClick() 
{

    isDestroyed = true;

    while (!allInterfaceObjects.empty()) 
    {
        if (allInterfaceObjects.back() != this)
        {
            if (!dynamic_cast<StartButton*>(allInterfaceObjects.back()))
                delete allInterfaceObjects.back();
        }
        allInterfaceObjects.pop_back();
    }

    StartButton* startButton = new StartButton(windowWidth / 2 - windowWidth / 6, windowHeight / 6, windowWidth / 3, windowHeight / 5, "res/textures/startButton.png", "res/textures/startButtonHovered.png", allInterfaceObjects, levelGenerator);
    allInterfaceObjects.push_back(startButton);

    HighscoresButton* highscoresButton = new HighscoresButton(windowWidth / 2 - windowWidth / 6, windowHeight / 2.5, windowWidth / 3, windowHeight / 5, "res/textures/highscoresButton.png","res/textures/highscoresButtonHovered.png", allInterfaceObjects , levelGenerator);
    allInterfaceObjects.push_back(highscoresButton);
}