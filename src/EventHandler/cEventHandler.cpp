/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include <iostream>
#include "cEventHandler.h"
#include "../Renderer/cRenderer.h"
#include "../GameLogic/cMapper.h"
#include "../GameLogic/cGameEntity.h"
#include "../common.h"
#include "../GameLogic/entityEnums.h"

namespace IOHandling {

bool cEventHandler::instanceFlag_ = false;
cEventHandler* cEventHandler::thisPointer_ = NULL;

cEventHandler* cEventHandler::getInstance()
{
    if (instanceFlag_)
    {
        return thisPointer_;
    }
    else
    {
        thisPointer_ = new cEventHandler();
        instanceFlag_ = true;
        return thisPointer_;
    }
}

cEventHandler::cEventHandler() :
    render_(renderer::cRenderer::getInstance()),
    mapper_(gamelogic::cMapper::getInstance()),
    xWindow_(render_->getRenderwindow())
{

}

void cEventHandler::update()
{
    sf::Vector3f inputCoord;
    Atom wmDelete=XInternAtom(xWindow_->getDisplay(), "WM_DELETE_WINDOW", True);
    XSetWMProtocols(xWindow_->getDisplay(), xWindow_->getWindow(), &wmDelete, 1);

    XSelectInput(xWindow_->getDisplay(), xWindow_->getWindow(), KeyPressMask);

    // Event loop checker
    while (XPending(xWindow_->getDisplay()))
    {
        XNextEvent(xWindow_->getDisplay(), &event_);
        if (event_.type == KeyPress)
        {
            appRunning = false;
            std::cout << "App closed!\n";
        }
        else if (event_.type == ClientMessage)
        {
            appRunning = false;
            std::cout << "App closed by closing the window!\n";
        }
    }
}

bool cEventHandler::hasPendingEvents()
{
    return XPending(xWindow_->getDisplay());
}

} // IOHandling
