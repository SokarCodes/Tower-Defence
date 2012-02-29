/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include <iostream>

#include <SFML/System.hpp>

#include "cGameEntity.h"
#include "cEnemyEntity.h"
#include "cMapper.h"

namespace gamelogic {

cEnemyEntity::cEnemyEntity(enemyType type, int x_coord, int y_coord) :
    entityName_(""),
    movespeed_(0),
    type_(type),
    state_(ALIVE)
{
    hitpoints_ = 100;
    x_coord_ = x_coord;
    y_coord_ = y_coord;
    std::cout << this->name() << ": Entity constructor!" << " --> ";
}    

void cEnemyEntity::initializeEntity()
{
    switch(type_)
    {
    case WALKING_ENEMY:
        entityName_ = "Walking_enemy";
        movespeed_ = 2;
        break;
    case FLYING_ENEMY:
        entityName_ = "Flying_enemy";
        movespeed_ = 5;
        break;
    case INVISIBLE_ENEMY:
        entityName_ = "Invisible_enemy";
        movespeed_ = 3;
        break;
    case FAST_ENEMY:
        entityName_ = "Fast_enemy";
        movespeed_ = 8;
        break;
    default:
        std::cout << "WARNING: initialize entity failed. No valid type acquired!\n";
    }
}

cEnemyEntity::~cEnemyEntity()
{
    std::cout << this->name() << ": Entity destruction!" << " --> ";
    //getMapper()->deleteEntity(this);
}

void cEnemyEntity::update(float frametime)
{
    // When enemy hitpoints are drained out, enemy is set to DECAY-state.
    // When in DECAY-state towers stop actions towards this enemy. DECAY-state
    // is kept for one frame and after that entity is put to DEAD-state and removed.
    // This guarantees that rendering layer renders last lethal shot to enemy.
    if (state_ == DEAD)
    {
        getMapper()->deleteEntity(this);
        return;
    }
    else if (state_ == DECAYING)
    {
        state_ = DEAD;
    }
    else if (state_ == ALIVE)
    {
        int random = sf::Randomizer::Random(0,3);

        switch(random)
        {
        case 0:
            if(x_coord_ > movespeed_)
                x_coord_ -= movespeed_;
            break;
        case 1:
            if(x_coord_ < 779)
                x_coord_ += movespeed_;
            break;
        case 2:
            if (y_coord_ > movespeed_)
                y_coord_ -= movespeed_;
            break;
        case 3:
            if (y_coord_ < 579)
                y_coord_ += movespeed_;
            break;
        }

        // For now, only thing enemyEntity can do is die away.
        if (hitpoints_ <= 0)
            state_ = DECAYING;
    }
}

enemyState cEnemyEntity::getState()
{
    return state_;
}

std::string cEnemyEntity::name()
{
    return entityName_;
}
} // namespace gamelogic
