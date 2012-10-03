/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#ifndef H_EVENTHANDLER
#define H_EVENTHANDLER

#include <SFML/System.hpp>
#include "X11/Xlib.h"


//#include "../Renderer/X11window.h"
#include "../common.h"

namespace renderer {
class cRenderer;
class X11Window;
}

namespace gamelogic {
class cMapper;
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

    /// Xlib event instance
    XEvent event_;

    /// X11 window instance
    renderer::X11Window* xWindow_;

};

} // IOHandling
#endif
