/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include "cGameEntity.h"
namespace gamelogic
{
// mapper_ definition
cMapper* cGameEntity::mapper_ = cMapper::getInstance();

void cGameEntity::inflictDamage(int dmg)
{
    this->hitpoints_ -= dmg;
}

} // namespace gamelogic
