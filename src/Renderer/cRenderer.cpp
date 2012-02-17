#include <iostream>
#include <sstream>
#include <cstdlib>
#include <vector>
#include <string>
#include "cRenderer.h"

#include "../GameLogic/cGameEntity.h"
#include "../GameLogic/entityEnums.h"

namespace renderer {

bool cRenderer::instanceFlag_ = false;
cRenderer* cRenderer::thisPointer_ = NULL;
gamelogic::cMapper* cRenderer::mapper_ = gamelogic::cMapper::getInstance();

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
    try
    {
        window_ = new sf::RenderWindow(sf::VideoMode(800,600,32), "Tower-Defence experimental build!", sf::Style::Close);
    }
    catch (std::bad_alloc&)
    {
        window_ = NULL;
        std::cout << "Renderwindow creation failure!\n";
        return;
    }
    text_ = new sf::String("lalla");
    // Set color and depth clear value
    glClearDepth(1.f);
    glClearColor(0.f, 0.f, 0.f, 0.f);

    // Enable Z-buffer read and write
    glEnable(GL_DEPTH_TEST);
    glDepthMask(GL_TRUE);

    // Setup a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.f, 1.f, 1.f, 500.f);

    window_->SetActive();
}

void cRenderer::update(float frametime)
{
    window_->PreserveOpenGLStates(true);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.f, 0.f, -200.f);
    glRotatef(frametime * 50, 1.f, 0.f, 0.f);
    glRotatef(frametime * 30, 0.f, 1.f, 0.f);
    glRotatef(frametime * 90, 0.f, 0.f, 1.f);

    glBegin(GL_QUADS);

        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f,  50.f, -50.f);
        glVertex3f( 50.f,  50.f, -50.f);
        glVertex3f( 50.f, -50.f, -50.f);

        glVertex3f(-50.f, -50.f, 50.f);
        glVertex3f(-50.f,  50.f, 50.f);
        glVertex3f( 50.f,  50.f, 50.f);
        glVertex3f( 50.f, -50.f, 50.f);

        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f(-50.f,  50.f, -50.f);
        glVertex3f(-50.f,  50.f,  50.f);
        glVertex3f(-50.f, -50.f,  50.f);

        glVertex3f(50.f, -50.f, -50.f);
        glVertex3f(50.f,  50.f, -50.f);
        glVertex3f(50.f,  50.f,  50.f);
        glVertex3f(50.f, -50.f,  50.f);

        glVertex3f(-50.f, -50.f,  50.f);
        glVertex3f(-50.f, -50.f, -50.f);
        glVertex3f( 50.f, -50.f, -50.f);
        glVertex3f( 50.f, -50.f,  50.f);

        glVertex3f(-50.f, 50.f,  50.f);
        glVertex3f(-50.f, 50.f, -50.f);
        glVertex3f( 50.f, 50.f, -50.f);
        glVertex3f( 50.f, 50.f,  50.f);

    glEnd();


    std::ostringstream frametimer;
    std::ostringstream towers, enemies;
    frametimer << frametime;
    std::string buffer;
    buffer.append("Frametime: ").append(frametimer.str());

    std::vector<gamelogic::cGameEntity*> enemyList = mapper_->getEnemyEntities();
    enemies << enemyList.size();
    buffer.append("\nEnemies: ").append(enemies.str());
    std::vector<gamelogic::cGameEntity*>::iterator iter = enemyList.begin();
    /*for (;iter < enemyList.end(); iter++)
    {
        enemyShape_->SetPosition((*iter)->getXPosition(), (*iter)->getYPosition());
        if ((*iter)->name() == "Walking_enemy")
            enemyShape_->SetColor(sf::Color::Magenta);
        else if ((*iter)->name() == "Flying_enemy")
            enemyShape_->SetColor(sf::Color::Blue);
        else if ((*iter)->name() == "Invisible_enemy")
            enemyShape_->SetColor(sf::Color::Green);
        else if ((*iter)->name() == "Fast_enemy")
            enemyShape_->SetColor(sf::Color::Red);
        window_->Draw(*enemyShape_);
    }*/
    std::vector<gamelogic::cGameEntity*> towerList = mapper_->getTowerEntities();
    towers << towerList.size();
    buffer.append(", Towers: ").append(towers.str());
    iter = towerList.begin();
    text_->SetText(buffer);
    /*for (;iter < towerList.end(); iter++)
    {
        towerShape_->SetPosition((*iter)->getXPosition(), (*iter)->getYPosition());
        if ((*iter)->name() == "Mortar_tower")
            towerShape_->SetColor(sf::Color::Cyan);
        else if ((*iter)->name() == "Arrow_tower")
            towerShape_->SetColor(sf::Color::White);
        else if ((*iter)->name() == "Ice_tower")
            towerShape_->SetColor(sf::Color::Yellow);
        else if ((*iter)->name() == "Special_tower")
            towerShape_->SetColor(sf::Color(100,50,220,200));
        window_->Draw(*towerShape_);
    }*/

    window_->Draw(*text_);
    window_->Display();
}
sf::RenderWindow* cRenderer::getRenderwindow()
{
    return window_;
}

}
