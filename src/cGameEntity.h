/* 
 * File:   cGameEntity.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 24, 2012, 8:25 PM
 */

#ifndef GAMEENTITY_H
#define	GAMEENTITY_H

#include <iostream>
#include "cMapper.h"

class cGameEntity {
public:
    /// Set derived class entity position in 2D space
    void setPosition(int x, int y) { x_coord_ = x; y_coord_ = y; }

    /// Get derived class entity position in 2D space
    void getPosition() { std::cout << "X: " << x_coord_ << " Y: " << y_coord_ << "\n"; }

    /// Return cMapper pointer to derived class.
    cMapper* getMapper() { return mapper_; }


    /// Virtual update method. Define in base class.
    virtual void update(float) = 0;

    /// Virtual method to set damage output
    virtual void setDamage(const unsigned int) {}

    /// Virtual method to set damage output RANGE
    virtual void setRange(const unsigned int) {}

    /// Virtual method to set target for attacking entity
    virtual void setTarget(cGameEntity*) {}

    /// Virtual method to set name of entity. Define in base class.
    virtual std::string name() = 0;

    /// Virtual destructor for proper derived/base chain dismantling.
    virtual ~cGameEntity() { std::cout << "cGameEntity destruction!" << "\n"; }

private:
    /// Entity X-coord in 2D space.
    int x_coord_;

    /// Entity Y-coord in 2D space.
    int y_coord_;

    /// Entity hitpoints. Entity removal when hitpoints <= 0
    int hitpoints_;

    /// cMapper pointer. Used in derived classes to inform cMapper of their destruction.
    static cMapper *mapper_;
};

#endif	/* GAMEENTITY_H */

