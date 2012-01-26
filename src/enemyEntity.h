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
    enemyEntity();
    ~enemyEntity();
    void update();
    std::string name();
private:
    std::string entityName;

};


#endif	/* ENEMYENTITY_H */

