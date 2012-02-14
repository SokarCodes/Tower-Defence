/*
 * File:   cTowerEntity.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 8:51 PM
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
    cTowerEntity(towerType, int, int);

    /// Destructor
    ~cTowerEntity();

    /// Set damage output for tower
    void setDamage(const unsigned int);

    /// Set maximum fire range for tower
    void setRange(const unsigned int);

    /// getRange
    int getRange();

    /// Update method for cTowerEntity
    void update(float);

    /// Get entity name
    std::string name();

    /// Initializer after creation
    void initializeEntity();

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
    int reloadTimeout_;

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

