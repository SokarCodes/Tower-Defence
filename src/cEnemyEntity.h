/* 
 * File:   cEnemyEntity.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 9:37 PM
 */

#ifndef ENEMYENTITY_H
#define	ENEMYENTITY_H

class cEnemyEntity : public cGameEntity {
public:
    /// Constructor
    cEnemyEntity();

    /// Destructor
    ~cEnemyEntity();

    /// Update function to hide more complex behaviour logic. Frametime as parameter.
    void update(float);

    /// Return entity name
    std::string name();

private:
    /// Entity name variable
    std::string entityName_;
};


#endif	/* ENEMYENTITY_H */

