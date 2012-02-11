/* 
 * File:   towerEnums.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 8:53 PM
 */

#ifndef TOWERENUMS_H
#define	TOWERENUMS_H
namespace gamelogic
{
// Enum for tower type.
enum towerType { MORTAR_TOWER,
                 ARROW_TOWER,
                 ICE_TOWER,
                 SPECIAL_TOWER };

// Enum for enemy type.
enum enemyType { WALKING_ENEMY,
                 FLYING_ENEMY,
                 INVISIBLE_ENEMY,
                 FAST_ENEMY};

// Splash damage boolean. Consider where AOE calculation are done!!
enum towerSplash { NO_SPLASH,
                   LITTLE_SPLASH,
                   HUGE_SPLASH,
                   AWESOME_SPLASH};

// Enum to add DamageOverTime type on target enemy.
enum towerEffect { NO_EFFECT,
                   SLOW_EFFECT,
                   BURN_EFFECT };
}

#endif	/* TOWERENUMS_H */

