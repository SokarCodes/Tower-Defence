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

void cRenderer::update(float frametime)
{
    xWindow->refresh();
    // Clear the screen to black
//    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
//    glClear( GL_COLOR_BUFFER_BIT );

//    // Draw a rectangle from the 2 triangles using 6 indices
//    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

//    // Swap buffers
//    window_->Display();

    /*    //window_->PreserveOpenGLStates(true);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(camX, camY, camZ);
    glRotatef(rotX, 1.0, 0.f, 0.f);
    glRotatef(rotY, 0.f, 1.f, 0.f);
    glRotatef(rotZ, 0.f, 0.f, 1.f);

    glBegin(GL_QUADS);
//    glVertex3f(-350.f, -350.f, -1.f);
//    glVertex3f(-350.f,  350.f, -1.f);
//    glVertex3f( 350.f,  350.f, -1.f);
//    glVertex3f( 350.f, -350.f, -1.f);

//    glVertex3f(-50.f, -50.f, 50.f);
//    glVertex3f(-50.f,  50.f, 50.f);
//    glVertex3f( 50.f,  50.f, 50.f);
//    glVertex3f( 50.f, -50.f, 50.f);

//    glVertex3f(-50.f, -50.f, -50.f);
//    glVertex3f(-50.f,  50.f, -50.f);
//    glVertex3f(-50.f,  50.f,  50.f);
//    glVertex3f(-50.f, -50.f,  50.f);

//    glVertex3f(50.f, -50.f, -50.f);
//    glVertex3f(50.f,  50.f, -50.f);
//    glVertex3f(50.f,  50.f,  50.f);
//    glVertex3f(50.f, -50.f,  50.f);

//    glVertex3f(-50.f, http://www.youtube.com/watch?v=lbqxkS2ssUI&feature=related#t=5m05s-50.f,  50.f);
//    glVertex3f(-50.f, -50.f, -50.f);
//    glVertex3f( 50.f, -50.f, -50.f);
//    glVertex3f( 50.f, -50.f,  50.f);

//    glVertex3f(-50.f, 50.f,  50.f);
//    glVertex3f(-50.f, 50.f, -50.f);
//    glVertex3f( 50.f, 50.f, -50.f);
//    glVertex3f( 50.f, 50.f,  50.f);
    glEnd();

    std::vector<gamelogic::cGameEntity*> towerList = mapper_->getTowerEntities();
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
