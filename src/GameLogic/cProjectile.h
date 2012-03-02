/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#ifndef PROJECTILE_H
#define PROJECTILE_H
#include <string>
#include "cGameEntity.h"
#include <SFML/System/Vector2.hpp>


namespace gamelogic {

class cProjectile : public cGameEntity
{
public:
    /// Projectile constructor.
    cProjectile(cGameEntity *owner, cGameEntity *target);

    /// Destructor
    ~cProjectile();

    /// Update method
    void update(float frametime);

    /// Return this projectile name. Possibly obsolete.
    std::string name();

    /// Initializes entity parameters.
    void initializeEntity();

    /// This is used to get unit vector from direction vector between projectile-target.
    void normalize(sf::Vector2f);

    /// Calculates distance between two vectors.
    double distance(sf::Vector2f, sf::Vector2f);
private:
    /// Name for this entity. Possibly obsolete.
    std::string entityName_;

    /// Entity movespeed on map. pix/s
    int movespeed_;

    /// Last move time for movement interpolation.
    float lastMoveTime_;

    /// Owner entity. Means tower basicly.
    cGameEntity *owner_;

    /// Target entity. To get direction vector.
    cGameEntity *target_;

    /// Direction vector.
    sf::Vector2f direction_;

};
} // gamelogic

#endif
