#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <vector>
#include <memory>

#include "Global.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "Rocket.h"
#include "Ball.h"
#include "CollisionManager.h"
#include "Block.h"
#include "Background.h"
#include "MyContainer.h"
#include "BallBlock.h"
#include "Image.h"
#include "InterfaceObject.h"
#include "StartButton.h"
#include "Text.h"
#include "HighScoresButton.h"
#include "GameOverScreen.h"

//transforms to range (-1,1)
//(isX == 1) if you are transforming x coordinate
float transformToOpenGl(const float& position,  const bool& isX)
{
    float result = 0.0f;
    if (isX == false)
    {
        result = -((position) / windowHeight * 2.0 - 1.0);
    }
    else
    {
        result = (position) / windowWidth * 2.0 - 1.0;
    }
    return result;
}

void rendererScene(std::vector<GameObject*>sceneObjects, Renderer& renderer, Shader& shader, VertexArray& va, VertexBuffer& vb, VertexBufferLayout& layout, IndexBuffer& ib, GLFWwindow* window)
{
    for (int i = 0; i < sceneObjects.size(); i++)
    {
        if (sceneObjects[i]->getIsDestroyed() == false)
        {
            float positionsTransformed[] = {
            transformToOpenGl(sceneObjects[i]->getX(), 1),  transformToOpenGl(sceneObjects[i]->getY() + sceneObjects[i]->getHeight(),0), 0.0f, 0.0f,
            transformToOpenGl(sceneObjects[i]->getX() + sceneObjects[i]->getWidth(), 1) , transformToOpenGl(sceneObjects[i]->getY() + sceneObjects[i]->getHeight(),0), 1.0f, 0.0f,
            transformToOpenGl(sceneObjects[i]->getX() + sceneObjects[i]->getWidth(), 1) , transformToOpenGl(sceneObjects[i]->getY(), 0) , 1.0f, 1.0f,
             transformToOpenGl(sceneObjects[i]->getX(), 1), transformToOpenGl(sceneObjects[i]->getY(), 0), 0.0f, 1.0f
            };

            vb.changeData(positionsTransformed, 4 * 4 * sizeof(float));
            ;
            sceneObjects[i]->getTexture()->Bind(1);

            renderer.Draw(va, ib, shader);

            if (dynamic_cast<Block*>(sceneObjects[i]))
            {
                Block* block = static_cast<Block*>(sceneObjects[i]);
                glEnable(GL_SCISSOR_TEST);

                glScissor(block->getX(), windowHeight - block->getY() - block->getHeight(), block->getWidth(), block->getHeight());

                std::vector<GameObject*> converted;
                for (int j = 0; j < block->getCracks().size(); j++)
                {
                    converted.push_back(block->getCrackAtIndex(j));
                }

                if (converted.size() > 0)
                    rendererScene(converted, renderer, shader, va, vb, layout, ib, window);
                glDisable(GL_SCISSOR_TEST);
            }
        }
    }
}

void rendererInterfaceObjects(std::vector<InterfaceObject*>interfaceObjects, Renderer& renderer, Shader& shader, VertexArray& va, VertexBuffer& vb, VertexBufferLayout& layout, IndexBuffer& ib, GLFWwindow* window)
{
    for (int i = 0; i < interfaceObjects.size(); i++)
    {
        if (interfaceObjects[i] != nullptr && interfaceObjects[i]->getIsDestroyed() == false)
        {
            float positionsTransformed[] = {
            transformToOpenGl(interfaceObjects[i]->getX(), 1),  transformToOpenGl(interfaceObjects[i]->getY() + interfaceObjects[i]->getHeight(),0), 0.0f, 0.0f,
            transformToOpenGl(interfaceObjects[i]->getX() + interfaceObjects[i]->getWidth(), 1) , transformToOpenGl(interfaceObjects[i]->getY() + interfaceObjects[i]->getHeight(),0), 1.0f, 0.0f,
            transformToOpenGl(interfaceObjects[i]->getX() + interfaceObjects[i]->getWidth(), 1) , transformToOpenGl(interfaceObjects[i]->getY(), 0) , 1.0f, 1.0f,
             transformToOpenGl(interfaceObjects[i]->getX(), 1), transformToOpenGl(interfaceObjects[i]->getY(), 0), 0.0f, 1.0f
            };
            vb.changeData(positionsTransformed, 4 * 4 * sizeof(float));
            va.AddBuffer(vb, layout);
            va.Bind();

            interfaceObjects[i]->getTexture()->Bind(1);

            renderer.Draw(va, ib, shader);
            if (dynamic_cast<Text*>(interfaceObjects[i]))
            {
                Text* text = static_cast<Text*>(interfaceObjects[i]);
                glEnable(GL_SCISSOR_TEST);

                glScissor(text->getX(), windowHeight - text->getY() - text->getHeight(), text->getWidth(), text->getHeight());

                std::vector<GameObject*> converted;
                for (int j = 0; j < text->getText().size(); j++)
                {
                    converted.push_back(text->getTextAtIndex(j));
                }

                if (converted.size() > 0)
                    rendererScene(converted, renderer, shader, va, vb, layout, ib, window);
                glDisable(GL_SCISSOR_TEST);
            }
        }
    }
}

void clearDestroyed(std::vector <GameObject*>& allSceneObjects)
{
    std::vector<GameObject*> newAllSceneObjects;

    for (int i = allSceneObjects.size()-1; i > 0; i--)
    {
        if (allSceneObjects[i]->getIsDestroyed() == false)
        {
            newAllSceneObjects.push_back(allSceneObjects[i]);
        }
        else
        {
            delete allSceneObjects[i];
        }
        allSceneObjects.pop_back();
    }
    for (int i = newAllSceneObjects.size(); i > 0; i--)
    {
        allSceneObjects.push_back(newAllSceneObjects[i - 1]);
    }
}

bool checkWin(std::vector<GameObject*>& allSceneObjects, int &points, Owner ballOwner, int currentLevel)
{
    bool win = true;
    bool areAllBlocksDestroyed = true;


    for (int i = 0; i < allSceneObjects.size(); i++)
    {
        if (dynamic_cast<Block*>(allSceneObjects[i]))
        {
            if (allSceneObjects[i]->getIsDestroyed() == false)
            {
                win = false;
                areAllBlocksDestroyed = false;
            }
        }
    }
    if (points >= LevelGenerator::getMinimumWinScore(currentLevel))
    {
        for (int i = 0; i < allSceneObjects.size(); i++)
        {
            if (dynamic_cast<Block*>(allSceneObjects[i]))
            {
                Block* block = static_cast<Block*>(allSceneObjects[i]);
                block->ballCollisionEffect(99999, player);
            }
        }
        return true;
    }
    if (areAllBlocksDestroyed == true && points <= LevelGenerator::getMinimumWinScore(currentLevel))
    {
        return false;
    }  
    for (int i = 0; i < allSceneObjects.size(); i++)
    {
        if (dynamic_cast<Ball*>(allSceneObjects[i]))
        {
            if (allSceneObjects[i]->getIsDestroyed() == true && ballOwner == enemy)
            {     
              
                for (int i = 0; i < allSceneObjects.size(); i++)
                {
                    if (dynamic_cast<Block*>(allSceneObjects[i]))
                    {
                        Block* block = static_cast<Block*>(allSceneObjects[i]);
                        block->ballCollisionEffect(99999, player);
                    }
                }

                return true;
            }
        }
    }


    return win;
}

bool checkLose(std::vector<GameObject*>& allSceneObjects, Owner ballOwner, int & points, int currentLevel)
{
    bool lose = true;
    for (int i = 0; i < allSceneObjects.size(); i++)
    {
        if (dynamic_cast<Ball*>(allSceneObjects[i]))
        {
            if (allSceneObjects[i]->getIsDestroyed() == false)
            {
                lose = false;
            }
        }
    }
    if (ballOwner == enemy)
    {
        lose = false;
    }

    bool areAllBlocksDestroyed = true;
    for (int i = 0; i < allSceneObjects.size(); i++)
    {
        if (dynamic_cast<Block*>(allSceneObjects[i]))
        {
            if (allSceneObjects[i]->getIsDestroyed() == false)
            {
                areAllBlocksDestroyed = false;
            }
        }
    }
    if (areAllBlocksDestroyed == true && points < LevelGenerator::getMinimumWinScore(currentLevel))
    {
        return true;
    }


    return lose;
}

struct UserData
{
    std::vector<InterfaceObject*>* allInterfaceObjects;
    bool& pause;

    UserData(std::vector<InterfaceObject*>* objects, bool& pauseState) : allInterfaceObjects(objects), pause(pauseState) {}
};

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        void* userPointer = glfwGetWindowUserPointer(window);
        if (UserData* userData = static_cast<UserData*>(userPointer))
        {
            for (int i = 0; i < userData->allInterfaceObjects->size(); i++)
            {

                if (xpos > (*userData->allInterfaceObjects)[i]->getX() && xpos < (*userData->allInterfaceObjects)[i]->getX() + (*userData->allInterfaceObjects)[i]->getWidth())
                {
                    if (ypos > (*userData->allInterfaceObjects)[i]->getY() && ypos < (*userData->allInterfaceObjects)[i]->getY() + (*userData->allInterfaceObjects)[i]->getHeight())
                    {
                        (*userData->allInterfaceObjects)[i]->onClick();
                        break;
                    }
                }

            }
        }
    }
}
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
    {
        void* userPointer = glfwGetWindowUserPointer(window);
        if (UserData* userData = static_cast<UserData*>(userPointer))
        {
            if (userData->pause == false)
            {
                userData->pause = true;
            }
            else
            {
                userData->pause = false;
            }
        }
    }
}
void hoverInterfaceObjects(int x, int y, std::vector<InterfaceObject*>& allInterfaceObjects)
{

    for (int i = 0; i < allInterfaceObjects.size(); i++)
    {
        if (x > allInterfaceObjects[i]->getX() && x < allInterfaceObjects[i]->getX() + allInterfaceObjects[i]->getWidth() && y > allInterfaceObjects[i]->getY() && y < allInterfaceObjects[i]->getY() + allInterfaceObjects[i]->getHeight())
        {
            allInterfaceObjects[i]->setIsHovered(true);
        }
        else
        {
            allInterfaceObjects[i]->setIsHovered(false);
        }
    }
}
void endGame(std::vector<InterfaceObject*>& allInterfaceObjects, std::vector<GameObject*>& allSceneObjects, bool& isGameFinished, StartButton*& startButton, HighscoresButton*& highscoresButton, LevelGenerator& levelGenerator, int& points)
{
    while (!allInterfaceObjects.empty())
    {
        delete allInterfaceObjects.back();
        allInterfaceObjects.pop_back();
    }
    while (!allSceneObjects.empty())
    {
        delete allSceneObjects.back();
        allSceneObjects.pop_back();
    }
    isGameFinished = true;
    startButton = new StartButton(windowWidth / 2 - windowWidth / 6, windowHeight / 6, windowWidth / 3, windowHeight / 5, "res/textures/startButton.png", "res/textures/startButtonHovered.png", allInterfaceObjects, levelGenerator);
    highscoresButton = new HighscoresButton(windowWidth / 2 - windowWidth / 6, windowHeight / 2.5, windowWidth / 3, windowHeight / 5, "res/textures/highscoresButton.png", "res/textures/highscoresButtonHovered.png", allInterfaceObjects, levelGenerator);
    allInterfaceObjects.push_back(new GameOverScreen(windowWidth * 0.25, windowHeight * 0.1, windowWidth * 0.5, windowHeight * 0.8, "res/textures/gameoverScreen.png", "res/textures/gameoverScreenHovered.png", 
    startButton, highscoresButton, allInterfaceObjects, isGameFinished, points));
    vector<InterfaceObject*> swapVec;
    for (int i = 0; i < allInterfaceObjects.size(); i++)
    {
        swapVec.push_back(allInterfaceObjects[i]);
    }
    for (int i = 0; i < allInterfaceObjects.size(); i++)
    {
        allInterfaceObjects[i] = swapVec[allInterfaceObjects.size() - i - 1];
    }

    levelGenerator.setCurrentLevel(1);
}
int main(void)
{


    int points = 0;
    Block::SetPlayerPoints(&points);

    std::vector<GameObject*> allSceneObjects;
    std::vector<InterfaceObject*> allInterfaceObjects;
    allSceneObjects.reserve(20);
    allInterfaceObjects.reserve(5);
    std::vector<Rocket*> rockets;

    CollisionManager collisionManager(allSceneObjects);

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;
    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(windowWidth, windowHeight, "Arkanoid", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK)
        std::cout << "glew error";
    else
        std::cout << "glew initialized properly\n";

    std::cout << glGetString(GL_VERSION);


    float positions[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 1.0f
    };
    unsigned int indicies[] = {
        0,1,2,
        2,3,0
    };

    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));

    VertexArray va;
    VertexBuffer vb(positions, 4 * 4 * sizeof(float));

    VertexBufferLayout layout;

    layout.Push<float>(2);
    layout.Push<float>(2);

    va.AddBuffer(vb, layout);
    IndexBuffer ib(indicies, 6);

    Shader shader("res/shaders/Basic.shader");

    Renderer renderer;

    shader.Bind();
    shader.SetUniform1i("u_Texture", 1);


    bool pause = false;
    UserData userData(&allInterfaceObjects, pause);


    glfwSetWindowUserPointer(window, &userData);

    LevelGenerator levelGenerator(allSceneObjects, allInterfaceObjects);

    StartButton* startButton = new StartButton(windowWidth / 2 - windowWidth/6, windowHeight/6, windowWidth/3, windowHeight/5, "res/textures/startButton.png", "res/textures/startButtonHovered.png", allInterfaceObjects, levelGenerator);
    allInterfaceObjects.push_back(startButton);



    HighscoresButton* highscoresButton = new HighscoresButton(windowWidth / 2 - windowWidth / 6, windowHeight / 2.5, windowWidth / 3, windowHeight / 5, "res/textures/highscoresButton.png", "res/textures/highscoresButtonHovered.png", allInterfaceObjects, levelGenerator);
    allInterfaceObjects.push_back(highscoresButton);


    float lastFramesCursorPosition[6];

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetKeyCallback(window, keyCallback);



    int loopCounter = 0;

    double xpos, ypos;

    //testing only DELETE LATER
    double lastTime = glfwGetTime();
    int frameCount = 0;

    bool isGameFinished = false;


    int ballX;
    Owner currentBallOwner = player;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        if (!pause)
        {
            glfwGetCursorPos(window, &xpos, &ypos);


                if (loopCounter % 20 == 0)//for optimization
                {
                    if (checkWin(allSceneObjects, points, currentBallOwner, levelGenerator.getCurrentLevel()) == true && StartButton::isGameStarted() == true && !isGameFinished)
                    {
                        if (levelGenerator.getCurrentLevel() < 5)
                        {
                            levelGenerator.increaseLevel();
                            levelGenerator.generate();
                            for (int i = 0; i < allInterfaceObjects.size(); i++)
                            {
                                if (dynamic_cast<Text*>(allInterfaceObjects[i]))
                                {
                                    Text* text = static_cast<Text*>(allInterfaceObjects[i]);
                                    if (text->getType() == Text::requiredPoints)
                                    {
                                        text->changeText("/" + std::to_string(levelGenerator.getMinimumWinScore(levelGenerator.getCurrentLevel())));
                                    }
                                }
                            }
                        }
                        else
                        {
                            endGame(allInterfaceObjects, allSceneObjects, isGameFinished, startButton, highscoresButton, levelGenerator, points);
                        }
                    }
                    else if (checkLose(allSceneObjects, currentBallOwner, points, levelGenerator.getCurrentLevel()) == true && StartButton::isGameStarted() == true && !isGameFinished)
                    {
                        endGame(allInterfaceObjects, allSceneObjects, isGameFinished, startButton, highscoresButton, levelGenerator, points);
                    }
                }

                
                for (int i = 0; i < allSceneObjects.size(); i++)
                {
                    if (dynamic_cast<Ball*>(allSceneObjects[i]))
                    {
                        Ball* ball = static_cast<Ball*>(allSceneObjects[i]);
                        ballX = ball->getX();
                        currentBallOwner = ball->getOwner();
                    }
                }
                for (int i = 0; i < allSceneObjects.size(); i++)
                {             
                    if (dynamic_cast<Rocket*>(allSceneObjects[i]))
                    {
                        Rocket* rocket = static_cast<Rocket*>(allSceneObjects[i]);
                        if (rocket->getOwner() == player)
                        {
                            rocket->setX(xpos - rocket->getWidth() / 2);
                            rocket->setSpeed(lastFramesCursorPosition[5] - lastFramesCursorPosition[0]);
                        }
                        if (rocket->getOwner() == enemy && currentBallOwner == enemy)
                        {
                            if (!(rocket->getX() + rocket->getWidth() / 2 - 10 < ballX && rocket->getX() + rocket->getWidth() / 2 + 10 > ballX))
                            {
                                if(rocket->getX() + rocket->getWidth() / 2 - 10 < ballX && rocket->getX() + rocket->getWidth() <= windowWidth * 0.96)
                                {
                                    rocket->setX(rocket->getX() + 8);
                                }
                                else if(rocket->getX() >= windowWidth * 0.04)
                                {
                                    rocket->setX(rocket->getX() - 8);
                                }
                            }
   
                        }
                    }
                }

                hoverInterfaceObjects(xpos, ypos, allInterfaceObjects);

                renderer.Clear();


                rendererScene(allSceneObjects, renderer, shader, va, vb, layout, ib, window);
                rendererInterfaceObjects(allInterfaceObjects, renderer, shader, va, vb, layout, ib, window);

                collisionManager.checkCollisions();


                lastFramesCursorPosition[5] = lastFramesCursorPosition[4];
                lastFramesCursorPosition[4] = lastFramesCursorPosition[3];
                lastFramesCursorPosition[3] = lastFramesCursorPosition[2];
                lastFramesCursorPosition[2] = lastFramesCursorPosition[1];
                lastFramesCursorPosition[1] = lastFramesCursorPosition[0];
                lastFramesCursorPosition[0] = xpos;


                loopCounter++;

                if (loopCounter % 300 == 0)//for optimization
                {
                    clearDestroyed(allSceneObjects);
                }
                if (loopCounter == INT_MAX)
                {
                    loopCounter = 0;
                }

                //TESTING DELETE LATER
                double currentTime = glfwGetTime();
                frameCount++;
                if (currentTime - lastTime >= 1.0)
                {
                    std::cout << "FPS: " << frameCount << std::endl;

                    frameCount = 0;
                    lastTime = currentTime;
                    std::cout << allInterfaceObjects.size() << std::endl;
                }


                /* Swap front and back buffers */
                GLCall(glfwSwapBuffers(window));
            }
        
        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }
    glfwTerminate();
    return 0;
}
