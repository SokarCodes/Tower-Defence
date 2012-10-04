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
    xWindow_ = new X11Window();
    renderContext_ = new GLESv2Context();
    xWindow_->open();
    renderContext_->bindWindow(xWindow_);
    renderContext_->init();
}

cRenderer::~cRenderer()
{
    delete renderContext_;
    delete xWindow_;
    instanceFlag_ = false;
}

void cRenderer::update(float frametime)
{
    xWindow_->refresh();

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
X11Window* cRenderer::getRenderwindow()
{
    return xWindow_;
}

// Not implemented properly.
void cRenderer::drawFPS(float spentTime)
{
    std::ostringstream frametimer;
    frametimer << std::fixed << std::setprecision(1);
    frametimer << spentTime;
}

void cRenderer::setBGcolor(float red, float green, float blue, float alpha)
{
    renderContext_->setBGcolor(red, green, blue, alpha);
}

}
