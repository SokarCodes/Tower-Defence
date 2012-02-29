/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#ifndef CMAPPER_H
#define	CMAPPER_H

#include <vector>
#include "entityEnums.h"
#include <SFML/System/Vector2.hpp>

namespace gamelogic {

class cGameEntity;

class cMapper {
public:
    // Consider this public segment as public API layer for Input/Interface/Etc.

    /// Destructor, sets instanceFlag to false so getInstance creates new on request
    ~cMapper() { instanceFlag_ = false; }

    /// Returns instance of this class
    static cMapper* getInstance();

    /// Adds new cTowerEntity to vector as cGameEntity
    bool addTower(towerType, sf::Vector2f position);

    /// Creates new enemy
    bool addEnemy(enemyType, sf::Vector2f position);

    /// Returns vectors for enemies and towers.
    std::vector<cGameEntity*> getEnemyEntities();
    std::vector<cGameEntity*> getTowerEntities();
    std::vector<cGameEntity*> getProjectileEntities();

    /// Update method. Calls update methods of all gameEntities.
    void update(float);

public:
    // This public segment is for derived classes and other more private use.

    /// Adds projectile entity to gamelogic
    bool addProjectile(cGameEntity*, cGameEntity*);

    /// deletes instance of cGameEntity from vector
    void deleteEntity(cGameEntity*);

    /// Check if entity exists
    bool entityExists(cGameEntity*);

    /// Check if entity in fire range
    bool isInRange(cGameEntity*, cGameEntity*);

    /// Returns closest possible target for querying entity.
    cGameEntity* getTarget(sf::Vector2f, int);

    /// Returns number of towers on map
    int getTowerCount();

    /// Returns number of enemies on map
    int getEnemyCount();

private:
    /// Private constructor because singleton class pointer is get from getInstance()
    cMapper() {}

    /// Vectors to store all entities in the map
    std::vector<cGameEntity*> enemyContainer_;
    std::vector<cGameEntity*> towerContainer_;
    std::vector<cGameEntity*> projectileContainer_;

    /// Singleton instance created flag
    static bool instanceFlag_;

    /// Pointer to store cMapper class if some class wants it.
    static cMapper *thisPointer_;
};
} // namespace gamelogic

#endif	/* CMAPPER_H */

