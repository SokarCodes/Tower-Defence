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
#include <SFML/System/Vector3.hpp>


namespace gamelogic {

class cProjectile : public cGameEntity
{
public:
    /// Projectile constructor.
    //cProjectile(cGameEntity *owner, cGameEntity *target);

    /// Default constructor
    cProjectile();

    /// Destructor
    ~cProjectile();

    /// Update method
    void update(float frametime);

    /// Return this projectile name. Possibly obsolete.
    std::string name() const;

    /// Initializes entity parameters.
    void initializeEntity(entityInitType type, sf::Vector3f position);

    /// Set target for this projectile. HACK! FIX THIS!
    void setTarget(cGameEntity* target) { target_ = target; }

    /// This is used to get unit vector from direction vector between projectile-target.
    sf::Vector3f normalize(sf::Vector3f);

    /// Calculates distance between two vectors.
    double distance(sf::Vector3f, sf::Vector3f);

    /// Dot product
    double dotProduct(sf::Vector3f vector1,sf::Vector3f vector2);
private:
    /// Name for this entity. Possibly obsolete.
    std::string entityName_;

    /// Entity movespeed on map. pix/s
    float movespeed_;

    /// Last move time for movement interpolation.
    float lastUpdateTime_;

    /// Owner entity. Means tower basicly.
    cGameEntity *owner_;

    /// Target entity. To get direction vector.
    cGameEntity *target_;

    /// Target location. For indirect fire.
    sf::Vector3f targetLocation_;

    /// Direction vector.
    sf::Vector3f direction_;

    /// Acceleration vector
    sf::Vector3f acceleration_;

    /// Velocity vector
    sf::Vector3f velocity_;

    /// Projectile type
    entityInitType type_;

    /// Splash size
    towerSplash splash_;

};
} // gamelogic

#endif
