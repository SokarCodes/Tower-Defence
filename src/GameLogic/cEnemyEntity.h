/*
 * File:   cEnemyEntity.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 9:37 PM
 */

#ifndef ENEMYENTITY_H
#define	ENEMYENTITY_H
#include <string>
namespace gamelogic {

class cEnemyEntity : public cGameEntity {
public:
    /// Constructor
    cEnemyEntity(int, int);

    /// Destructor
    ~cEnemyEntity();

    /// Update function to hide more complex behaviour logic. Frametime as parameter.
    void update(float);

    /// Return entity name
    std::string name();

private:
    /// Entity name variable
    std::string entityName_;

    /// Entity move speed
    unsigned short int movespeed_;
};

} // namespace gamelogic
#endif	/* ENEMYENTITY_H */

