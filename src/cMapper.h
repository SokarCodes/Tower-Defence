/* 
 * File:   cMapper.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on February 1, 2012, 7:28 PM
 */

#ifndef CMAPPER_H
#define	CMAPPER_H

#include <vector>
class cGameEntity;

class cMapper {
public:
    /// Destructor, sets instanceFlag to false so getInstance creates new on request
    ~cMapper() { instanceFlag_ = false; }

    /// Returns instance of this class
    static cMapper* getInstance();

    /// Adds cGameEntity to vector
    void add(cGameEntity*);

    /// Shows names of gameEntities in vector. Obsolete.
    void showEntities();

    /// Update method. Calls update methods of all gameEntities.
    void update(float);

    /// deletes instance of cGameEntity from vector
    void deleteInstance(cGameEntity*);

    /// Returns closest possible target for querying entity.
    cGameEntity* getTarget(int, int, int);
private:
    /// Private constructor because singleton class pointer is get from getInstance()
    cMapper() {}

    /// Vector to store all entities in the map
    std::vector<cGameEntity*> entityContainer_;

    /// Singleton instance created flag
    static bool instanceFlag_;

    /// Pointer to store cMapper class if some class wants it.
    static cMapper *thisPointer_;
};


#endif	/* CMAPPER_H */

