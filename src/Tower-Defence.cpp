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
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
    std::cout << "Hello tower defense - experimental branch!\n";

    bool appRunning = true;
    
    // Initialize variables for gameloop timer logic
    sf::Clock clock;
    const int framerate = 30;
    float framestartTime = 0;
    float difference = 0;
    float sleepTime = 0;
    float frameBudget = 1/(float)framerate;

    // Create event mapper
    sf::Event Event;

    // Singleton mapper class which updates all gameEntities
    gamelogic::cMapper *mapper;

    // Singleton renderer class which handles all graphics
    renderer::cRenderer *render;

    try {
        mapper = gamelogic::cMapper::getInstance();
        render = renderer::cRenderer::getInstance();
    } catch (std::bad_alloc& e) {
        std::cout << "Initial memory allocation for mapper and renderer failed! " << e.what() << "\n";
        return EXIT_FAILURE;
    }

    // Inputmapper
    const sf::Input& Input = render->getRenderwindow()->GetInput();

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

        // Event loop checker
        while (render->getRenderwindow()->GetEvent(Event))
        {
            // Window closed
            if (Event.Type == sf::Event::Closed)
            {
                std::cout << "User interrupt close window!\n";
                appRunning = false;
                render->getRenderwindow()->Close();
            }

            // Escape key pressed
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            {
                std::cout << "User interrupt ESC-key!\n";
                appRunning = false;
                render->getRenderwindow()->Close();
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Z))
            {
                mapper->addEnemy(gamelogic::WALKING_ENEMY, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::X))
            {
                mapper->addEnemy(gamelogic::FLYING_ENEMY, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::C))
            {
                mapper->addEnemy(gamelogic::INVISIBLE_ENEMY, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::V))
            {
                mapper->addEnemy(gamelogic::FAST_ENEMY, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::A))
            {
                mapper->addTower(gamelogic::MORTAR_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::S))
            {
                mapper->addTower(gamelogic::ARROW_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D))
            {
                mapper->addTower(gamelogic::ICE_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F))
            {
                mapper->addTower(gamelogic::SPECIAL_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }
            // Mouse button left pressed
            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.MouseButton.Button == sf::Mouse::Left))
            {
                //mapper->addTower(gamelogic::MORTAR_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }

            // Mouse button right pressed
            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.MouseButton.Button == sf::Mouse::Right))
            {
                mapper->addTower(gamelogic::SPECIAL_TOWER, Event.MouseButton.X, Event.MouseButton.Y);
            }
        }
    }
    // End of gameloop. Destroy mapper.
    delete render;
    delete mapper;


    return EXIT_SUCCESS;
}

