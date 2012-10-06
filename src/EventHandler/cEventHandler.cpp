/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include <iostream>
#include "cEventHandler.h"
#include "../Renderer/cRenderer.h"
#include "../Renderer/X11window.h"
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
    Atom wmDelete=XInternAtom(xWindow_->getDisplay(), "WM_DELETE_WINDOW", True);
    XSetWMProtocols(xWindow_->getDisplay(), xWindow_->getWindow(), &wmDelete, 1);

    XSelectInput(xWindow_->getDisplay(), xWindow_->getWindow(), KeyPressMask);

    // Event loop checker
    while (XPending(xWindow_->getDisplay()))
    {
        XNextEvent(xWindow_->getDisplay(), &event_);
        if (event_.type == KeyPress)
        {
            switch (XLookupKeysym(&event_.xkey, 0))
            {
            case XK_q:
                render_->setBGcolor(0.1,0,0,0);
                break;
            case XK_w:
                render_->setBGcolor(0,0.1,0,0);
                break;
            case XK_e:
                render_->setBGcolor(0,0,0.1,0);
                break;
            case XK_r:
                render_->setBGcolor(0,0,0,0.1);
                break;
            case XK_a:
                render_->setBGcolor(-0.1,0,0,0);
                break;
            case XK_s:
                render_->setBGcolor(0,-0.1,0,0);
                break;
            case XK_d:
                render_->setBGcolor(0,0,-0.1,0);
                break;
            case XK_f:
                render_->setBGcolor(0,0,0,-0.1);
                break;
            default:
                appRunning = false;
                std::cout << "App closed!\n";
            }
        }
        // Check for client messages and specific wmDelete to close the window.
        else if (event_.type == ClientMessage && event_.xclient.data.l[0] == long(wmDelete))
        {
            appRunning = false;
            std::cout << "App closed by closing the window!\n";
        }
    }
}

} // IOHandling
