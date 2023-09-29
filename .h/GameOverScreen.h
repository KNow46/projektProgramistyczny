#pragma once
#include "InterfaceObject.h"
#include "StartButton.h"
#include "HighscoresButton.h"
#include <vector>
#include <fstream>

class GameOverScreen : public InterfaceObject
{
public:
    GameOverScreen(int x, int y, int width, int height, std::string texturePath, std::string textureHoveredPath, StartButton* startButton, HighscoresButton* highscoresButton, std::vector<InterfaceObject*>& allInterfaceObjects, bool& isGameLost, int& points);

    void onClick();

private:
    StartButton* startButton;
    HighscoresButton* highscoresButton;
    bool& isGameLost;
    std::vector<InterfaceObject*>& allInterfaceObjects;
    int highscores[5];
};