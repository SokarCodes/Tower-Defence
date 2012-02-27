/*
 * File:   main.cpp
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 8:02 PM
 */
#include <iostream>
#include <cstdlib>
#include <sstream>

#include "GameLogic/cGameEntity.h"
#include "GameLogic/cMapper.h"
#include "GameLogic/entityEnums.h"
#include "Renderer/cRenderer.h"
#include "EventHandler/cEventHandler.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "common.h"

bool appRunning;

int main(int argc, char** argv)
{
    std::cout << "Hello tower defense - experimental branch!\n";
    
    appRunning = true;

    // Initialize variables for gameloop timer logic
    sf::Clock clock;
    const int framerate = 30;
    float framestartTime = 0;
    float difference = 0;
    float sleepTime = 0;
    float frameBudget = 1/(float)framerate;

    // Singletons
    gamelogic::cMapper *mapper;
    renderer::cRenderer *render;
    IOHandling::cEventHandler *InputOutput;

    try {
        mapper = gamelogic::cMapper::getInstance();
        render = renderer::cRenderer::getInstance();
        InputOutput = IOHandling::cEventHandler::getInstance();
    } catch (std::bad_alloc& e) {
        std::cout << "Initial memory allocation for mapper and renderer failed! " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    // Start running the clock just before gameloop
    clock.Reset();

    // Gameloop
    while(appRunning)
    {
        // Get current framestart time
        framestartTime = clock.GetElapsedTime();

        // Update game logic and renderer instance.
        mapper->update(framestartTime);
        render->update(framestartTime);
        InputOutput->update();

        // Get time elapsed in game logic update
        difference = clock.GetElapsedTime() - framestartTime;

        // If difference is smaller than budgeted, rest until next frame
        if (difference < frameBudget)
        {
            // Rendering budgets:
            // 60fps = 16,667ms
            // 30fps = 33,333ms
            // 10fps = 100ms
            //  5fps = 200ms
            sleepTime = frameBudget - difference;
            // Sleep for rest of the frame
            sf::Sleep(sleepTime);
        }
    }
    // End of gameloop. Destroy mapper.
    delete InputOutput;
    delete render;
    delete mapper;


    return EXIT_SUCCESS;
}

