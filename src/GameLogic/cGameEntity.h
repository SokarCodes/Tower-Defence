/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#ifndef GAMEENTITY_H
#define	GAMEENTITY_H

#include <iostream>
#include <SFML/System/Vector3.hpp>
#include "cMapper.h"

namespace gamelogic {

class cGameEntity {
public:
    /// Cause single target damage to a entity.
    void inflictDamage(int);

    /// Set derived class entity position in 2D space
    void setPosition(sf::Vector3f pos) { position_ = pos; }

    sf::Vector3f& getPosition() { return position_; }

    /// Get maximum fire range for tower
    virtual int getRange() { return 0; }

    /// Virtual function for checking if tower has enemy. Overloaded in cTowerEntity. Returns false if enemyEntity.
    virtual bool hasEnemy() { return false; }

    /// Returns towers target enemy.
    virtual cGameEntity* getEnemy() {return 0;}

    /// Returns towers last fire time. If enemyEntity, return 0.
    virtual float lastFireTime() {return 0;}

    /// Returns enemy state. Overloaded in cEnemyEntity.
    virtual enemyState getState() { return ALIVE; }

    /// Virtual update method. Define in base class.
    virtual void update(float) = 0;

    /// Virtual method to set damage output
    virtual void setDamage(const unsigned int) {}

    /// Virtual method to set damage output RANGE
    virtual void setRange(const unsigned int) {}

    /// Virtual method to set name of entity. Define in base class.
    virtual std::string name() = 0;

    /// Initialize all entity variables
    virtual void initializeEntity(entityInitType type, sf::Vector3f position) = 0;

    /// Set entity target enemy
    virtual void setTarget(cGameEntity* target) {}

    /// Virtual destructor for proper derived/base chain dismantling.
    virtual ~cGameEntity() { }

protected:
    /// Return cMapper pointer to derived class.
    cMapper* getMapper() { return mapper_; }

    /// Position
    sf::Vector3f position_;

    /// Entity hitpoints. Entity removal when hitpoints <= 0
    int hitpoints_;

private:
    /// cMapper pointer. Used in derived classes to inform cMapper of their destruction.
    static cMapper *mapper_;
};
} // namespace gamelogic
#endif	/* GAMEENTITY_H */

