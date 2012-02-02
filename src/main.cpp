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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    /// Just testing classes
    cout << "Hello tower defense!" << endl;

    gameEntity *tower;
    gameEntity *enemy;
    cMapper *mapper;

    try {
        mapper = cMapper::getInstance();
        tower = new towerEntity(mapper);
        enemy = new enemyEntity(mapper);
    }
    catch (bad_alloc&)
    {
        return EXIT_FAILURE;
    }

    mapper->add(tower);
    mapper->add(enemy);
    // This update does not initiate fire sequence on tower entity.
    mapper->update();
    mapper->showEntities();
    // Target has been acquired on last update so now fire sequence initiates.
    mapper->update();
    delete enemy;
    mapper->update();
    mapper->showEntities();
    delete tower;
    mapper->update();
    mapper->showEntities();
    delete mapper;
    
    return EXIT_SUCCESS;
}

