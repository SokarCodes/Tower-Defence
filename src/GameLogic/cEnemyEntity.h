/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#ifndef ENEMYENTITY_H
#define	ENEMYENTITY_H
#include <string>
#include <SFML/System/Vector2.hpp>
#include "entityEnums.h"
namespace gamelogic {
class cGameEntity;

class cEnemyEntity : public cGameEntity {
public:
    /// Constructor
    cEnemyEntity(enemyType type, sf::Vector2f position);

    /// Destructor
    ~cEnemyEntity();

    /// Update function to hide more complex behaviour logic. Frametime as parameter.
    void update(float);

    /// Return entity name
    std::string name();

    /// Initializer after creation
    void initializeEntity();

    /// Returns enemy entity state
    enemyState getState();

private:
    /// Entity name variable
    std::string entityName_;

    /// Entity move speed
    unsigned short int movespeed_;

    /// Entity type
    enemyType type_;

    /// State
    enemyState state_;
};

} // namespace gamelogic
#endif	/* ENEMYENTITY_H */

