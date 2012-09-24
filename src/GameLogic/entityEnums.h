/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#ifndef TOWERENUMS_H
#define	TOWERENUMS_H
namespace gamelogic
{

// Splash damage boolean. Consider where AOE calculation are done!!
enum towerSplash { NO_SPLASH,
                   LITTLE_SPLASH,
                   HUGE_SPLASH,
                   AWESOME_SPLASH};

// Enum to add DamageOverTime type on target enemy.
enum towerEffect { NO_EFFECT,
                   SLOW_EFFECT,
                   BURN_EFFECT };

// Enum for enemy current state.
enum enemyState { ALIVE,
                  DECAYING,
                  DEAD };

enum entityType { TOWER,
                  ENEMY,
                  PROJECTILE };

enum entityInitType { MORTAR_TOWER,
                      ARROW_TOWER,
                      ICE_TOWER,
                      SPECIAL_TOWER,
                      WALKING_ENEMY,
                      FLYING_ENEMY,
                      INVISIBLE_ENEMY,
                      FAST_ENEMY,
                      HOMING,
                      INDIRECT,
                      INSTANT};
}


#endif	/* TOWERENUMS_H */

