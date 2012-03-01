/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

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
#include "cProjectile.h"

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

bool cMapper::addTower(towerType type, sf::Vector2f position)
{
    cGameEntity *entity;

    switch (type)
    {
    case MORTAR_TOWER:
    case ARROW_TOWER:
    case ICE_TOWER:
    case SPECIAL_TOWER:
        entity = dynamic_cast<cGameEntity*>(new cTowerEntity(type, position));
        entity->initializeEntity();
        towerContainer_.push_back(entity);
        std::cout << "Added cGameEntity: " << entity->name() << " to container! Position(" << entity->getPosition().x << "," << entity->getPosition().y << ").\n";
        return true;
    default:
        std::cout << "No valid tower type given!\n";
        return false;
    }
}

bool cMapper::addEnemy(enemyType type, sf::Vector2f position)
{
    cGameEntity *enemy;

    switch (type)
    {
    case FLYING_ENEMY:
    case WALKING_ENEMY:
    case INVISIBLE_ENEMY:
    case FAST_ENEMY:
        enemy = dynamic_cast<cGameEntity*>(new cEnemyEntity(type, position));
        enemy->initializeEntity();
        enemyContainer_.push_back(enemy);
        std::cout << "Added cGameEntity: " << enemy->name() << " to container! Position(" << enemy->getPosition().x << "," << enemy->getPosition().y << ").\n";
        return true;
    default:
        std::cout << "No valit enemy type given!\n";
        return false;
    }
}

bool cMapper::addProjectile(cGameEntity *owner, cGameEntity *target)
{
    cGameEntity *entity;
    try
    {
        entity = dynamic_cast<cGameEntity*>(new cProjectile(owner,target));
    }
    catch (std::bad_alloc &e)
    {
        std::cout << "Unable to allocate new projectile: " << e.what() << "\n";
        return false;
    }
    entity->initializeEntity();
    projectileContainer_.push_back(entity);
    return true;

}

void cMapper::update(float frametime) {
    std::vector<cGameEntity*>::iterator iter;

    for (iter = towerContainer_.begin();iter < towerContainer_.end();++iter)
        (*iter)->update(frametime);
    for (iter = enemyContainer_.begin();iter < enemyContainer_.end();++iter)
        (*iter)->update(frametime);
    for (iter = projectileContainer_.begin();iter < projectileContainer_.end();++iter)
        (*iter)->update(frametime);
}

cGameEntity* cMapper::getTarget(sf::Vector2f position, int range)
{
    cGameEntity *closestEntity = NULL;
    float closestRange = 999999;

    std::vector<cGameEntity*>::iterator iter;

    for (iter = enemyContainer_.begin();iter < enemyContainer_.end();++iter)
    {
        sf::Vector2f enemyPos = (*iter)->getPosition();
        sf::Vector2f diff = position - enemyPos;
        double range = sqrt(pow(diff.x,2) + pow(diff.y,2));
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
    std::vector<cGameEntity*>::iterator iter = enemyContainer_.begin();
    for (;iter < enemyContainer_.end();++iter)
        if ((*iter) == instance)
        {
            delete (*iter);
            enemyContainer_.erase(iter);
            return;
        }
    // instance is tower if we are this far.
    iter = towerContainer_.begin();
    for (;iter < towerContainer_.end();++iter)
        if ((*iter) == instance)
        {
            delete (*iter);
            towerContainer_.erase(iter);
            return;
        }
    iter = projectileContainer_.begin();
    for (;iter < projectileContainer_.end();++iter)
        if ((*iter) == instance)
        {
            delete (*iter);
            projectileContainer_.erase(iter);
            return;
        }
}

bool cMapper::entityExists(cGameEntity * ent)
{
    std::vector<cGameEntity*>::iterator iter = enemyContainer_.begin();
    for (;iter < enemyContainer_.end();++iter)
        if ((*iter) == ent)
        {
            return true;
        }
    return false;
}

bool cMapper::isInRange(cGameEntity *enemy, cGameEntity *tower)
{
    sf::Vector2f diff = tower->getPosition() - enemy->getPosition();
    double range = sqrt(pow(diff.x,2) + pow(diff.y,2));
    if (range <= tower->getRange())
        return true;
    else
        return false;
}

std::vector<cGameEntity*> cMapper::getEnemyEntities()
{
    return enemyContainer_;
}

std::vector<cGameEntity*> cMapper::getTowerEntities()
{
    return towerContainer_;
}

std::vector<cGameEntity*> cMapper::getProjectileEntities()
{
    return projectileContainer_;
}

int cMapper::getEnemyCount()
{
    return enemyContainer_.size();
}

int cMapper::getTowerCount()
{
    return towerContainer_.size();
}
} // namespace gamelogic