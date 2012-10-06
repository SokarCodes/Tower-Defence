/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#ifndef ENEMYENTITY_H
#define	ENEMYENTITY_H
#include <string>
#include <SFML/System/Vector3.hpp>
#include "entityEnums.h"
namespace gamelogic {
class cGameEntity;

class cEnemyEntity : public cGameEntity {
public:
    /// Constructor
    //cEnemyEntity(entityInitType type, sf::Vector3f position);

    /// Default constructor
    cEnemyEntity();

    /// Destructor
    ~cEnemyEntity();

    /// Update function to hide more complex behaviour logic. Frametime as parameter.
    void update(float);

    /// Return entity name
    std::string name() const;

    /// Initializer after creation
    void initializeEntity(entityInitType type, sf::Vector3f position);

    /// Returns enemy entity state
    enemyState getState() const;

private:
    /// Entity name variable
    std::string entityName_;

    /// Entity move speed
    unsigned short int movespeed_;

    /// Entity type
    entityInitType type_;

    /// State
    enemyState state_;
};

} // namespace gamelogic
#endif	/* ENEMYENTITY_H */

