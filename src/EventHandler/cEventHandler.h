/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#ifndef H_EVENTHANDLER
#define H_EVENTHANDLER

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "../common.h"

namespace renderer {
class cRenderer;
}

namespace gamelogic {
class cMapper;
class cGameEntity;
}

namespace IOHandling {

class cEventHandler
{
public:
    /// Destructor, sets instanceFlag to false so getInstance creates new on request
    ~cEventHandler() { instanceFlag_ = false; }

    /// Returns singleton pointer
    static cEventHandler* getInstance();

    /// Update method to parse events
    void update();

private:
    /// private constructor because singleton. Instance is gotten from getInstance
    cEventHandler();

    /// Flag to tell if instance made or not
    static bool instanceFlag_;

    /// Pointer to this class if instance made.
    static cEventHandler* thisPointer_;

    /// Renderer instance for event grabbing
    renderer::cRenderer* render_;

    /// GameLogic instance
    gamelogic::cMapper* mapper_;

    /// SFML event instance
    sf::Event event_;

    /// SFML input instance
    const sf::Input& input_;

    bool mouseleftDown_;

    gamelogic::cGameEntity *entity_;



};

} // IOHandling
#endif
