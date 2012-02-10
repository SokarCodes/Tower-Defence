/* 
 * File:   cTowerEntity.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 8:51 PM
 */
#ifndef TOWERENTITY_H
#define	TOWERENTITY_H

#include <string>
class cGameEntity;

class cTowerEntity : public cGameEntity
{
public:
    /// Constructor
    cTowerEntity(int x, int y);

    /// Destructor
    ~cTowerEntity();

    /// Set damage output for tower
    void setDamage(const unsigned int);

    /// Set maximum fire range for tower
    void setRange(const unsigned int);

    /// Update method for cTowerEntity
    void update(float);

    /// Get entity name
    std::string name();

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
};

#endif	/* TOWERENTITY_H */

