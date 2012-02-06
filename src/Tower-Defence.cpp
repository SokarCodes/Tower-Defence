/* 
 * File:   main.cpp
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 8:02 PM
 */
#include <iostream>
#include <cstdlib>
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
    float framestartTime = 0;
    float difference = 0;
    float sleepTime = 0;
    float frameBudget = 1/(float)framerate;

    // Create SFML renderwindow
    sf::RenderWindow window(sf::VideoMode(800,600,32), "Tower-Defence!");

    // Create event mapper
    sf::Event Event;

    // Singleton mapper class which updates all gameEntities
    cMapper *mapper;

    try {
        mapper = cMapper::getInstance();
    } catch (bad_alloc&) {
        return EXIT_FAILURE;
    }

    // Add couple gameEntities to mapper
    mapper->add(dynamic_cast<cGameEntity*> (new cTowerEntity));
    mapper->add(dynamic_cast<cGameEntity*> (new cEnemyEntity));

    sf::String Text("DERP!");
    Text.SetFont(sf::Font::GetDefaultFont());
    Text.SetStyle(sf::String::Bold | sf::String::Italic | sf::String::Underlined);
    Text.SetStyle(sf::String::Regular);
    Text.SetColor(sf::Color(128, 128, 0));
    Text.SetRotation(0.f);
    Text.SetScale(2.f, 2.f);
    Text.Move(100.f, 200.f);

    // Start running the clock just before gameloop
    clock.Reset();
    // Gameloop
    while(appRunning)
    {
        window.Display();
        window.Draw(Text);

        // Get current framestart time
        framestartTime = clock.GetElapsedTime();
        cout << "----\nFramestartTime = " << framestartTime << "\n";
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
        }
    }
    // Target has been acquired on last update so now fire sequence initiates.
    delete mapper;

    return EXIT_SUCCESS;
}

