// Standard libraries
#include <iostream>
#include <vector>
#include <math.h>
#include <string>

// project libraries
#include "cGameEntity.h"
#include "cMapper.h"
#include "cTowerEntity.h"
#include "cEnemyEntity.h"
#include "entityEnums.h"

namespace gamelogic {

cMapper* cMapper::thisPointer_ = NULL;
bool cMapper::instanceFlag_ = false;

cMapper* cMapper::getInstance() {
    if (!instanceFlag_)
    {
        thisPointer_ = new cMapper();
        instanceFlag_ = true;
        return thisPointer_;
    }
    else
    {
        return thisPointer_;
    }
}

bool cMapper::addTower(towerType type, int x_coord, int y_coord)
{
    // This method is undergoing radical changes. Implement tower addition
    // in a way API call can be made only by giving tower type.
    // simplifies events from render layer user input to gamelogic.
    cGameEntity *entity;
    switch (type)
    {
    case MORTAR_TOWER:
        entity = dynamic_cast<cGameEntity*>(new cTowerEntity(type, x_coord, y_coord));
        entity->initializeEntity();
        entityContainer_.push_back(entity);
        std::cout << "Added cGameEntity: " << entity->name() << " to container! Position(" << entity->getXPosition() << "," << entity->getYPosition() << ").\n";
        return true;
        break;
    case ARROW_TOWER:
        entity = dynamic_cast<cGameEntity*>(new cTowerEntity(type, x_coord, y_coord));
        entity->initializeEntity();
        entityContainer_.push_back(entity);
        std::cout << "Added cGameEntity: " << entity->name() << " to container! Position(" << entity->getXPosition() << "," << entity->getYPosition() << ").\n";
        return true;
        break;
    default:
        std::cout << "DERP\n";
        return false;
    }
}

std::vector<cGameEntity*> cMapper::getEntities() {
    return entityContainer_;
}

void cMapper::update(float frametime) {
    std::vector<cGameEntity*>::iterator iter = entityContainer_.begin();

    for (;iter < entityContainer_.end();iter++)
        (*iter)->update(frametime);
}

cGameEntity* cMapper::getTarget(int x, int y, int range)
{
    // Brute force approach. Iterate through every enemyEntities and
    // calculate distance between querying tower and enemy.
    // Return enemyEntity ptr if in range.
    cGameEntity *closestEntity = NULL;
    float closestRange = 999999;

    std::vector<cGameEntity*>::iterator iter = entityContainer_.begin();

    for (;iter < entityContainer_.end();iter++)
        if ((*iter)->name() == "Enemy")
        {
            double diffX = x - (*iter)->getXPosition();
            double diffY = y - (*iter)->getYPosition();
            double range = sqrt(pow(diffX,2) + pow(diffY,2));
            if (range < closestRange)
            {
                closestRange = range;
                closestEntity = (*iter);
            }
        }
    if (closestRange <= range)
    {
        std::cout << "Closest enemy was " << closestRange << " distance away.\n";
        return closestEntity;
    }
    else
    {
        return NULL;
    }
}

void cMapper::deleteEntity(cGameEntity *instance)
{
    std::vector<cGameEntity*>::iterator iter = entityContainer_.begin();
    for (;iter < entityContainer_.end();iter++)
        if ((*iter) == instance)
        {
            delete (*iter);
            entityContainer_.erase(iter);
        }
}

bool cMapper::entityExists(cGameEntity * ent)
{
    std::vector<cGameEntity*>::iterator iter = entityContainer_.begin();
    for (;iter < entityContainer_.end();iter++)
        if ((*iter) == ent)
        {
            return true;
        }
    return false;
}

bool cMapper::isInRange(cGameEntity * enemy, cGameEntity *tower)
{
    double diffX = tower->getXPosition() - enemy->getXPosition();
    double diffY = tower->getYPosition() - enemy->getYPosition();
    double range = sqrt(pow(diffX,2) + pow(diffY,2));
    if (range <= tower->getRange())
        return true;
    else
        return false;
}

int cMapper::getEnemyCount()
{
    int count = 0;
    std::vector<cGameEntity*>::iterator iter = entityContainer_.begin();
    for (;iter < entityContainer_.end();iter++)
        if ((*iter)->name() == "Enemy")
        {
            ++count;
        }
    return count;
}

int cMapper::getTowerCount()
{
    int count = 0;
    std::vector<cGameEntity*>::iterator iter = entityContainer_.begin();
    for (;iter < entityContainer_.end();iter++)
        if ((*iter)->name() == "Tower")
        {
            ++count;
        }
    return count;
}
} // namespace gamelogic
