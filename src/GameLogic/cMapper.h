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
#include <SFML/System/Vector3.hpp>
#include <stack>

namespace gamelogic {

class cGameEntity;

class cMapper {
public:
    // Consider this public segment as public API layer for Input/Interface/Etc.

    /// Destructor, sets instanceFlag to false so getInstance creates new on request
    ~cMapper();

    /// Returns instance of this class
    static cMapper* getInstance();

    /// Adds new cTowerEntity to vector as cGameEntity
    bool addTower(entityInitType, sf::Vector3f position);

    /// Creates new enemy
    bool addEnemy(entityInitType, sf::Vector3f position);

    /// Returns vectors for enemies and towers.
    std::vector<cGameEntity*> getEnemyEntities();
    std::vector<cGameEntity*> getTowerEntities();
    std::vector<cGameEntity*> getProjectileEntities();

    /// Update method. Calls update methods of all gameEntities.
    void update(float);

public:
    // This public segment is for derived classes and other more private use.

    /// Deals AOE damage according to parameters
    void dealAOEDamage(sf::Vector3f location, int range, int damage);

    /// Adds projectile entity to gamelogic
    bool addProjectile(cGameEntity*, cGameEntity*);

    /// deletes instance of cGameEntity from vector
    void deleteEntity(cGameEntity*, entityInitType);

    /// Check if entity in fire range
    bool isInRange(cGameEntity*, cGameEntity*);

    /// Returns closest possible target for querying entity.
    cGameEntity* getTarget(sf::Vector3f, int);

    /// Returns number of towers on map
    int getTowerCount() const;

    /// Returns number of enemies on map
    int getEnemyCount() const;

    /// Calculates distance between two vectors.
    double distance(sf::Vector3f, sf::Vector3f) const;

private:
    /// Private constructor because singleton class pointer is get from getInstance()
    cMapper();

    /// Vectors to store all entities in the map
    std::vector<cGameEntity*> enemyContainer_;
    std::vector<cGameEntity*> towerContainer_;
    std::vector<cGameEntity*> projectileContainer_;

    /// Dynamically allocated stack containers
    std::stack<cGameEntity*> enemyStack_;
    std::stack<cGameEntity*> towerStack_;
    std::stack<cGameEntity*> projectileStack_;


    /// Singleton instance created flag
    static bool instanceFlag_;

    /// Pointer to store cMapper class if some class wants it.
    static cMapper *thisPointer_;
};
} // namespace gamelogic

#endif	/* CMAPPER_H */

