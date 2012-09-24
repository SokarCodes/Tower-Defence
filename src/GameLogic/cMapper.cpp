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

cMapper::cMapper()
{
    std::cout << "Creating tower stack...";
    cGameEntity *entity;
    for (int count = 0; count < 5000; ++count)
    {
        entity = dynamic_cast<cGameEntity*>(new cTowerEntity());
        towerStack_.push(entity);
    }
    std::cout << "DONE! Size: " << towerStack_.size() * sizeof(entity) / 1024 << "kB.\n";

    std::cout << "Creating enemy stack...";
    for (int count = 0; count < 5000; ++count)
    {
        entity = dynamic_cast<cGameEntity*>(new cEnemyEntity());
        enemyStack_.push(entity);
    }
    std::cout << "DONE! Size: " << enemyStack_.size() * sizeof(entity) / 1024 << "kB.\n";

    std::cout << "Creating projectile stack...";
    for (int count = 0; count < 12000; ++count)
    {
        entity = dynamic_cast<cGameEntity*>(new cProjectile());
        projectileStack_.push(entity);
    }
    std::cout << "DONE! Size: " << projectileStack_.size() * sizeof(entity) / 1024 << "kB.\n\n";
}

cMapper::~cMapper()
{
    instanceFlag_ = false;
    std::cout << "Removing entities...";
    std::vector<cGameEntity*>::iterator iter;
    for (iter = towerContainer_.begin();iter < towerContainer_.end();++iter)
    {
        delete (*iter);
        towerContainer_.erase(iter);
    }
    for (iter = enemyContainer_.begin();iter < enemyContainer_.end();++iter)
    {
        delete (*iter);
        enemyContainer_.erase(iter);
    }
    for (iter = projectileContainer_.begin();iter < projectileContainer_.end();++iter)
    {
        delete (*iter);
        projectileContainer_.erase(iter);
    }
    cGameEntity *entity;
    while (!enemyStack_.empty())
    {
        entity = enemyStack_.top();
        enemyStack_.pop();
        delete entity;
    }
    while (!towerStack_.empty())
    {
        entity = towerStack_.top();
        towerStack_.pop();
        delete entity;
    }
    while (!projectileStack_.empty())
    {
        entity = projectileStack_.top();
        projectileStack_.pop();
        delete entity;
    }
    std::cout << "DONE!\n";
}

bool cMapper::addTower(entityInitType type, sf::Vector3f position)
{
    if (!towerStack_.empty())
    {
        cGameEntity *entity;

        switch (type)
        {
        case MORTAR_TOWER:
        case ARROW_TOWER:
        case ICE_TOWER:
        case SPECIAL_TOWER:
            // Take entity from towerStack
            entity = towerStack_.top();
            // Pop tower from stack
            towerStack_.pop();
            // Initialize entity variables
            entity->initializeEntity(type, position);
            // Place entity in update loop
            towerContainer_.push_back(entity);
            return true;
        default:
            std::cout << "No valid tower type given!\n";
            return false;
        }
    }
    else
    {
        std::cout << "No more towers in stack!\n";
        return false;
    }
}

bool cMapper::addEnemy(entityInitType type, sf::Vector3f position)
{
    std::cout <<"position: " << position.x << "," << position.y << "," <<position.z << "\n";
    if (!enemyStack_.empty())
    {
        cGameEntity *enemy;

        switch (type)
        {
        case FLYING_ENEMY:
        case WALKING_ENEMY:
        case INVISIBLE_ENEMY:
        case FAST_ENEMY:
            // Take entity from enemyStack
            enemy = enemyStack_.top();
            // Pop enemy from stack
            enemyStack_.pop();
            // Initialize entity variables
            enemy->initializeEntity(type, position);
            // Place entity in update loop
            enemyContainer_.push_back(enemy);
            return true;
        default:
            std::cout << "No valid enemy type given!\n";
            return false;
        }
    }
    else
    {
        std::cout << "No more enemies in stack!\n";
        return false;
    }
}

bool cMapper::addProjectile(cGameEntity *owner, cGameEntity *target)
{
    if (!projectileStack_.empty())
    {
    cGameEntity *entity;
    entity = projectileStack_.top();
    projectileStack_.pop();
    entity->setTarget(target);
    entity->initializeEntity(INDIRECT,owner->getPosition());
    projectileContainer_.push_back(entity);
    return true;
    }
    else
    {
        std::cout << "No more projectiles in stack!\n";
        return false;
    }

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

cGameEntity* cMapper::getTarget(sf::Vector3f position, int range)
{
    cGameEntity *closestEntity = NULL;
    float closestRange = 999999;

    std::vector<cGameEntity*>::iterator iter;

    for (iter = enemyContainer_.begin();iter < enemyContainer_.end();++iter)
    {
        sf::Vector3f enemyPos = (*iter)->getPosition();
        sf::Vector3f diff = position - enemyPos;
        double range = sqrt(pow(diff.x,2) + pow(diff.y,2) + pow(diff.z,2));
        if (range < closestRange)
        {
            closestRange = range;
            closestEntity = (*iter);
        }
    }
    if (closestRange <= range)
    {
        return closestEntity;
    }
    else
    {
        return NULL;
    }
}

void cMapper::deleteEntity(cGameEntity *instance, entityInitType type)
{
    std::vector<cGameEntity*>::iterator iter;
    switch (type)
    {
    case MORTAR_TOWER:
    case ARROW_TOWER:
    case ICE_TOWER:
    case SPECIAL_TOWER:
        for (iter = towerContainer_.begin();iter < towerContainer_.end();++iter)
            if ((*iter) == instance)
            {
                cGameEntity* ent = (*iter);
                towerStack_.push(ent);
                towerContainer_.erase(iter);
            }
        break;
    case WALKING_ENEMY:
    case FLYING_ENEMY:
    case INVISIBLE_ENEMY:
    case FAST_ENEMY:
        for (iter = enemyContainer_.begin();iter < enemyContainer_.end();++iter)
            if ((*iter) == instance)
            {
                cGameEntity* ent = (*iter);
                enemyStack_.push(ent);
                enemyContainer_.erase(iter);
            }
        break;
    case INDIRECT:
    case HOMING:
    case INSTANT:
        for (iter = projectileContainer_.begin();iter < projectileContainer_.end();++iter)
            if ((*iter) == instance)
            {
                cGameEntity* ent = (*iter);
                projectileStack_.push(ent);
                projectileContainer_.erase(iter);
            }
        break;
    default:
        std::cout << "WARNING: Unable to delete entity. Type given unknown!\n";
    }


    // instance is tower if we are this far.




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
    sf::Vector3f diff = tower->getPosition() - enemy->getPosition();
    double range = sqrt(pow(diff.x,2) + pow(diff.y,2));
    if (range <= tower->getRange())
        return true;
    else
        return false;
}

void cMapper::dealAOEDamage(sf::Vector3f location, int range, int damage)
{
    std::vector<cGameEntity*> enemiesInAOE;
    std::vector<cGameEntity*>::iterator iter = enemyContainer_.begin();
    for (;iter < enemyContainer_.end(); ++iter)
    {
        if (distance(location,(*iter)->getPosition()) <= range)
            enemiesInAOE.push_back(*iter);
    }
    for (iter = enemiesInAOE.begin();iter < enemiesInAOE.end(); ++iter)
        (*iter)->inflictDamage(damage);
}

double cMapper::distance(sf::Vector3f A, sf::Vector3f B)
{
    sf::Vector3f diff = B-A;
    double distance = sqrt(pow(diff.x,2)+pow(diff.y,2));
    return distance;
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
