/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#ifndef TOWERENTITY_H
#define	TOWERENTITY_H

#include <string>
#include "entityEnums.h"

namespace gamelogic {
class cGameEntity;

class cTowerEntity : public cGameEntity
{
public:
    /// Constructor
    cTowerEntity(towerType type, sf::Vector2f position);

    /// Destructor
    ~cTowerEntity();

    /// Set damage output for tower
    void setDamage(const unsigned int);

    /// Set maximum fire range for tower
    void setRange(const unsigned int);

    /// getRange
    int getRange();

    /// Get tower type
    towerType getType();

    /// Update method for cTowerEntity
    void update(float);

    /// Get entity name
    std::string name();

    /// Initializer after creation
    void initializeEntity();

    /// Function for checking if tower has enemy.
    bool hasEnemy();

    /// Return target enemy.
    cGameEntity* getEnemy() { return enemy_; }

    /// Return last fire time.
    float lastFireTime() { return lastShotTime_; }

private:
    /// Fire method. Launches projectile towards enemy entity.
    void fire();

    /// Acquires target enemy entity if possible
    void acquireTarget();

    /// Target entity. NULL if no target acquired.
    cGameEntity* enemy_;

    /// Tower damage output
    unsigned int damage_;

    /// Tower maximum range
    unsigned int range_;

    /// Reload timeout
    float reloadTimeout_;

    /// Last shot timestamp
    float lastShotTime_;

    /// Entity name
    std::string entityName_;

    /// Tower type
    towerType type_;

    /// tower lifetime
    float lifetime_;

};
} // namespace gamelogic

#endif	/* TOWERENTITY_H */

