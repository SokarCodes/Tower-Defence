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
enum towerType { MORTAR = 0,
                 ARROW,
                 ICE,
                 SPECIAL };

// Splash damage boolean. Consider where AOE calculation are done!!
enum towerSplash { NO = 0,
                   YES };

// Enum to add DamageOverTime type on target enemy.
enum towerEffect { NONE = 0,
                   SLOW,
                   BURN };
}

// Where tower can attack.
enum attackType { GROUND = 0,
                  AIR,
                  BOTH };

#endif	/* TOWERENUMS_H */

