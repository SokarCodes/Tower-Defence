/* 
 * File:   main.cpp
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 8:02 PM
 */
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "cGameEntity.h"
#include "cTowerEntity.h"
#include "cEnemyEntity.h"
#include "cMapper.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
/*
 * 
 */
int main(int argc, char** argv) {

    /// Just testing classes
    cout << "Hello tower defense!\n";

    bool appRunning = true;
    
    // Initialize variables for gameloop timer logic
    sf::Clock clock;
    const int framerate = 60;
    float framestartTime = 0; //fix this
    float difference = 0;
    float sleepTime = 0;
    float frameBudget = 1/(float)framerate;

    // Create SFML renderwindow
    sf::RenderWindow window(sf::VideoMode(800,600,32), "Tower-Defence!", sf::Style::Close);

    // Create event mapper
    sf::Event Event;

    // Testing renderwindow draw shapes
    sf::Shape towerShape = sf::Shape::Circle(0.f, 0.f, 5.f, sf::Color::White);
    sf::Shape enemyShape = sf::Shape::Rectangle(0.f, 0.f, 10.f, 10.f, sf::Color::Blue);
    sf::String text("Frametime");


    // Inputmapper
    const sf::Input& Input = window.GetInput();

    // Singleton mapper class which updates all gameEntities
    cMapper *mapper;

    try {
        mapper = cMapper::getInstance();
    } catch (bad_alloc&) {
        return EXIT_FAILURE;
    }

    //mapper->add(dynamic_cast<cGameEntity*> (new cEnemyEntity));

    // Start running the clock just before gameloop
    clock.Reset();

    // Gameloop
    while(appRunning)
    {
        window.Clear();

        std::ostringstream frametimer;
        frametimer << framestartTime;
        std::string buffer;
        buffer.append("Frametime: ").append(frametimer.str());
        text.SetText(buffer);

        std::vector<cGameEntity*> entityList = mapper->getEntities();
        std::vector<cGameEntity*>::iterator iter = entityList.begin();
        for (;iter < entityList.end(); iter++)
        {
            if ((*iter)->name() == "Enemy")
            {
                enemyShape.SetPosition((*iter)->getXPosition(), (*iter)->getYPosition());
                window.Draw(enemyShape);
            }
            else
            {
                towerShape.SetPosition((*iter)->getXPosition(), (*iter)->getYPosition());
                window.Draw(towerShape);
            }
        }

        window.Draw(text);
        window.Display();


        // Get current framestart time
        framestartTime = clock.GetElapsedTime();

        // Update game logic. Here only mapper->update()
        mapper->update(framestartTime);

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
        while (window.GetEvent(Event))
        {
            // Window closed
            if (Event.Type == sf::Event::Closed)
            {
                cout << "User interrupt close window!\n";
                appRunning = false;
                window.Close();
            }

            // Escape key pressed
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            {
                cout << "User interrupt ESC-key!\n";
                appRunning = false;
                window.Close();
            }

            // Mouse button left pressed
            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Left))
            {
                mapper->add(dynamic_cast<cGameEntity*> (new cTowerEntity(Input.GetMouseX(),Input.GetMouseY())));
            }

            // Mouse button right pressed
            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Right))
            {
                mapper->add(dynamic_cast<cGameEntity*> (new cEnemyEntity(Input.GetMouseX(),Input.GetMouseY())));
            }
        }
    }
    // Target has been acquired on last update so now fire sequence initiates.
    delete mapper;

    return EXIT_SUCCESS;
}

