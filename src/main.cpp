/* 
 * File:   main.cpp
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 8:02 PM
 */
//#include <iostream>
#include <cstdlib>

#include "gameEntity.h"
#include "towerEntity.h"
#include "enemyEntity.h"
#include "cMapper.h"
#include <ctime>

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    /// Just testing classes
    cout << "Hello tower defense!" << endl;

   clock_t start;           // timer test
   start = clock();         // timer test
   double diff;             // timer test
   static int frames = 0;   // timer test
   int delta = 0;           // timer test


   for ( int i = 0; i < 100000; i++ )   // timer test
       cout << i << "\n";               // timer test

    cMapper *mapper;

    try {
        mapper = cMapper::getInstance();
    }
    catch (bad_alloc&)
    {
        return EXIT_FAILURE;
    }

    mapper->add(dynamic_cast<gameEntity*>(new towerEntity(mapper)));
    mapper->add(dynamic_cast<gameEntity*>(new enemyEntity(mapper)));
    // This update does not initiate fire sequence on tower entity.

    mapper->update();
    mapper->showEntities();

    // Testing timer
    diff = ( std::clock() - start ) / (double)CLOCKS_PER_SEC;
    cout << diff << "\n";

    // Target has been acquired on last update so now fire sequence initiates.
    delete mapper;
    
    return EXIT_SUCCESS;
}

