/* Tower-Defence
 *
 * Author: Jukka Vatjus-Anttila <jukka.vatjusanttila@gmail.com>
 *
 * For conditions of distribution and use, see copyright notice in LICENSE.txt
 */

#include <iostream>
#include <iomanip>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>

#include "cRenderer.h"
#include "../common.h"

#include "../GameLogic/cGameEntity.h"
#include "../GameLogic/entityEnums.h"
#include "X11window.h"
#include "GLESv2context.h"

float camX, camY, camZ;
float rotX, rotY, rotZ;
namespace renderer {

bool cRenderer::instanceFlag_ = false;
cRenderer* cRenderer::thisPointer_ = NULL;
gamelogic::cMapper* cRenderer::mapper_ = gamelogic::cMapper::getInstance();

// Shader sources
const char* vertexSource =
        "#version 150\n"
        "in vec2 position;"
        "in vec3 color;"
        "out vec3 Color;"
        "void main() {"
        "	Color = color;"
        "	gl_Position = vec4( position, 0.0, 1.0 );"
        "}";
const char* fragmentSource =
        "#version 150\n"
        "in vec3 Color;"
        "out vec4 outColor;"
        "void main() {"
        "	outColor = vec4( Color, 1.0 );"
        "}";

cRenderer* cRenderer::getInstance()
{
    if (instanceFlag_)
    {
        return thisPointer_;
    }
    else
    {
        thisPointer_ = new cRenderer();
        instanceFlag_ = true;
        return thisPointer_;
    }
}

cRenderer::cRenderer()
{
    xWindow = new X11Window();
    renderContext = new GLESv2Context();
    xWindow->open();
    renderContext->bindWindow(xWindow);
    renderContext->init();
}

cRenderer::~cRenderer()
{
    delete renderContext;
    delete xWindow;
    instanceFlag_ = false;
}

void cRenderer::update(float frametime)
{
    xWindow->refresh();

    // Testing X11 event system. This is going to be refined and moved to eventhandler class.
    Atom wmDelete=XInternAtom(xWindow->getDisplay(), "WM_DELETE_WINDOW", True);
    XSetWMProtocols(xWindow->getDisplay(), xWindow->getWindow(), &wmDelete, 1);

    XSelectInput(xWindow->getDisplay(), xWindow->getWindow(), KeyPressMask);
    XEvent events;

    while (XPending(xWindow->getDisplay()))
    {
        XNextEvent(xWindow->getDisplay(), &events);
        if (events.type == KeyPress)
        {
            appRunning = false;
            std::cout << "App closed!\n";
        }
        else if (events.type == ClientMessage)
        {
            appRunning = false;
            std::cout << "App closed by closing the window!\n";
        }
    }

    // Event testing ends here.


 /*   std::vector<gamelogic::cGameEntity*> towerList = mapper_->getTowerEntities();
    std::vector<gamelogic::cGameEntity*>::iterator iter = towerList.begin();

    for (;iter < towerList.end(); iter++)
    {
        sf::Vector3f position = (*iter)->getPosition();
        glPointSize(2);
        glColor3f(0,0.8,0);
        glBegin(GL_POINTS);
        glVertex3f(position.x, position.y, position.z);
        glEnd();
        //window_->Draw(*towerShape_);
    }

    std::vector<gamelogic::cGameEntity*> enemyList = mapper_->getEnemyEntities();
    iter = enemyList.begin();
    for (;iter < enemyList.end(); iter++)
    {
        sf::Vector3f position = (*iter)->getPosition();
        glColor3f(0.9,0,0.8);
        glBegin(GL_POINTS);
        glVertex3f(position.x, position.y, position.z);
        glEnd();
        //window_->Draw(*enemyShape_);
    }

    std::vector<gamelogic::cGameEntity*> projectileList = mapper_->getProjectileEntities();
    iter = projectileList.begin();
    for (;iter < projectileList.end(); iter++)
    {
        sf::Vector3f position = (*iter)->getPosition();
        glColor3f(0.9,0.9,0.9);
        glBegin(GL_POINTS);
        glVertex3f(position.x, position.y, position.z);
        glEnd();
        //window_->Draw(*projectile_);
    }
*/
}
//sf::Window* cRenderer::getRenderwindow()
//{
//    return window_;
//}

// Not implemented properly.
void cRenderer::drawFPS(float spentTime)
{
    std::ostringstream frametimer;
    frametimer << std::fixed << std::setprecision(1);
    frametimer << spentTime;
}

}
