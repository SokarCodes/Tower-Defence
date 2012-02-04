/* 
 * File:   cMapper.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on February 1, 2012, 7:28 PM
 */

#ifndef CMAPPER_H
#define	CMAPPER_H

#include <vector>
class gameEntity;

class cMapper {
public:
    /// Destructor, sets instanceFlag to false so getInstance creates new on request
    ~cMapper() { instanceFlag = false; }

    /// Returns instance of this class
    static cMapper* getInstance();

    /// Adds gameEntity to vector
    void add(gameEntity*);

    /// Shows names of gameEntities in vector. Obsolete.
    void showEntities();

    /// Update method. Calls update methods of all gameEntities.
    void update(float);

    /// deletes instance of gameEntity from vector
    void deleteInstance(gameEntity*);

    /// Returns closest possible target for querying entity.
    gameEntity* getTarget(
        //give asker coordinates as parameter?
        );
private:
    /// Private constructor because singleton class pointer is get from getInstance()
    cMapper() {}

    /// Vector to store all entities in the map
    std::vector<gameEntity*> entityContainer;

    /// Singleton instance created flag
    static bool instanceFlag;

    /// Pointer to store cMapper class if some class wants it.
    static cMapper *thisPointer;
};


#endif	/* CMAPPER_H */

