/* 
 * File:   main.cpp
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 8:02 PM
 */
#include <iostream>
#include <cstdlib>
#include "gameEntity.h"
#include "towerEntity.h"
#include "enemyEntity.h"
#include "cMapper.h"
#include <SFML/System.hpp>

using namespace std;
/*
 * 
 */
int main(int argc, char** argv) {

    /// Just testing classes
    cout << "Hello tower defense!" << endl;
    
    // Initialize variables for gameloop timer logic
    sf::Clock clock;
    const int framerate = 2;
    float framestartTime = 0;
    float difference = 0;
    float sleepTime = 0;
    float frametime = 1/(float)framerate;
    cout << frametime;
    
    // Singleton mapper class which updates all gameEntities
    cMapper *mapper;

    try {
        mapper = cMapper::getInstance();
    } catch (bad_alloc&) {
        return EXIT_FAILURE;
    }

    // Add couple gameEntities to mapper
    mapper->add(dynamic_cast<gameEntity*> (new towerEntity(mapper)));
    mapper->add(dynamic_cast<gameEntity*> (new enemyEntity(mapper)));

    // Gameloop
    while(1)
    {
        // Get current framestart time
        framestartTime = clock.GetElapsedTime();
        // Update game logic. Here only mapper->update()
        mapper->update(framestartTime);
        // Get time elapsed in game logic update
        difference = clock.GetElapsedTime() - framestartTime;
        
        // If difference is smaller than budgeted, rest until next frame
        if (difference < frametime)
        {
            // Rendering budgets:
            // 60fps = 16,667ms
            // 30fps = 33,333ms
            // 10fps = 100ms
            //  5fps = 200ms
            sleepTime = frametime - difference;
            // Sleep for rest of the frame
            sf::Sleep(sleepTime);
        }
    }
    // Target has been acquired on last update so now fire sequence initiates.
    delete mapper;

    return EXIT_SUCCESS;
}

