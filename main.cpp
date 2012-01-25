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

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    /// Just testing classes
    cout << "Hello tower defense!" << endl;
    gameEntity *tower = new towerEntity();
    gameEntity *enemy = new enemyEntity();
    tower->update();
    enemy->update();
    tower->setDamage(6);
    tower->setRange(10);
    tower->setTarget(enemy);
    tower->update();
    
    delete tower;
    delete enemy;
    return EXIT_SUCCESS;
}

