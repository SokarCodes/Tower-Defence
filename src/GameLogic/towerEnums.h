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
// Enum for tower damage type. GROUND fires at ground targets, AIR fires air targets and BOTH fires at ...dun-dun-duuu... both targets.
enum towerType { GROUND = 0,
                AIR, 
                BOTH };

// Splash damage boolean. Consider where AOE calculation are done!!
enum towerSplash { NO = 0,
                YES };

// Enum to add DOT type on target enemy.
enum towerEffect { NONE = 0,
                SLOW,
                BURN };
}

#endif	/* TOWERENUMS_H */

