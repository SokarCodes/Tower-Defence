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
    float frameBudget = 1/(float)framerate;
    //cout << "Framebudget = " << frameBudget*1000 << "ms\n";
    
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

    // Start running the clock just before gameloop
    clock.Reset();
    // Gameloop
    while(1)
    {
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
    }
    // Target has been acquired on last update so now fire sequence initiates.
    delete mapper;

    return EXIT_SUCCESS;
}

