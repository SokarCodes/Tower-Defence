/* 
 * File:   enemyEntity.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 9:37 PM
 */

#ifndef ENEMYENTITY_H
#define	ENEMYENTITY_H
class cMapper;

class enemyEntity : public gameEntity {
public:
	// Constructor
    enemyEntity(cMapper *mapper);
	// Destructor
    ~enemyEntity();
	// Update funktion to hide more complex behaviour logic
    void update(long);
	// Return entity name
    std::string name();
private:
	// Entity name variable
    std::string entityName_;
    cMapper *mapper_;

};


#endif	/* ENEMYENTITY_H */

