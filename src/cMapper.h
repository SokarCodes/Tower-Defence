/* 
 * File:   cMapper.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on February 1, 2012, 7:28 PM
 */

#ifndef CMAPPER_H
#define	CMAPPER_H
#include <vector>
#include "gameEntity.h"

class cMapper {
private:
    cMapper() {}
    std::vector<gameEntity*> entityContainer;
    static bool instanceFlag;
    static cMapper *thisPointer;
public:
    ~cMapper() { instanceFlag = false; }
    static cMapper* getInstance();
    void add(gameEntity*);
    void showEntities();
    void update();
    void deleteInstance(gameEntity*);
    gameEntity* getTarget(
        //give asker coordinates as parameter?
        );
    
};


#endif	/* CMAPPER_H */

