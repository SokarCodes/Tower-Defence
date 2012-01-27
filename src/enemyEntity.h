/* 
 * File:   enemyEntity.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 9:37 PM
 */

#ifndef ENEMYENTITY_H
#define	ENEMYENTITY_H
class enemyEntity : public gameEntity {
public:
	// Constructor
    enemyEntity();
	// Destructor
    ~enemyEntity();
	// Update funktion to hide more complex behaviour logic
    void update();
	// Return entity name
    std::string name();
private:
	// Entity name variable
    std::string entityName;

};


#endif	/* ENEMYENTITY_H */

