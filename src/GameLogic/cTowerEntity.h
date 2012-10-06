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
    //cTowerEntity(entityInitType type, sf::Vector3f position);

    /// Default constructor
    cTowerEntity();

    /// Destructor
    ~cTowerEntity();

    /// Set maximum fire range for tower
    void setRange(const unsigned int);

    /// getRange
    int getRange() const;

    /// Get tower type
    entityInitType getType();

    /// Update method for cTowerEntity
    void update(float);

    /// Get entity name
    std::string name() const;

    /// Initializer after creation
    void initializeEntity(entityInitType type, sf::Vector3f position);

    /// Function for checking if tower has enemy.
    bool hasEnemy() const;

    /// Return target enemy.
    cGameEntity* getEnemy() const { return enemy_; }

    /// Return last fire time.
    float lastFireTime() const { return lastShotTime_; }

    /// Fire angle calculator
    bool isInRange();

    /// Calculates distance between two vectors.
    double distance(sf::Vector3f, sf::Vector3f) const;

private:
    /// Fire method. Launches projectile towards enemy entity.
    void fire();

    /// Acquires target enemy entity if possible
    void acquireTarget();

    /// Target entity. NULL if no target acquired.
    cGameEntity* enemy_;

    /// Tower maximum range
    unsigned int range_;

    /// Fire angle
    float fireAngle_;

    /// Reload timeout
    float reloadTimeout_;

    /// Last shot timestamp
    float lastShotTime_;

    /// Entity name
    std::string entityName_;

    /// Tower type
    entityInitType type_;

    /// tower lifetime
    float lifetime_;

};
} // namespace gamelogic

#endif	/* TOWERENTITY_H */

