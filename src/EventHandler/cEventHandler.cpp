#include <iostream>
#include "cEventHandler.h"
#include "../Renderer/cRenderer.h"

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
    input_(render_->getRenderwindow()->GetInput())
{

}

void cEventHandler::update()
{

    // Event loop checker
    while (render_->getRenderwindow()->GetEvent(event_))
    {
        // Window closed
        if (event_.Type == sf::Event::Closed)
        {
            std::cout << "User interrupt close window!\n";
            appRunning = false;
            render_->getRenderwindow()->Close();
        }

        // Escape key pressed
        if ((event_.Type == sf::Event::KeyPressed) && (event_.Key.Code == sf::Key::Escape))
        {
            std::cout << "User interrupt ESC-key!\n";
            appRunning = false;
            render_->getRenderwindow()->Close();
        }

        if ((event_.Type == sf::Event::KeyPressed) && (event_.Key.Code == sf::Key::Z))
        {
            mapper_->addEnemy(gamelogic::WALKING_ENEMY, input_.GetMouseX(), input_.GetMouseY());
        }

        if ((event_.Type == sf::Event::KeyPressed) && (event_.Key.Code == sf::Key::X))
        {
            mapper_->addEnemy(gamelogic::FLYING_ENEMY, input_.GetMouseX(), input_.GetMouseY());
        }

        if ((event_.Type == sf::Event::KeyPressed) && (event_.Key.Code == sf::Key::C))
        {
            mapper_->addEnemy(gamelogic::INVISIBLE_ENEMY, input_.GetMouseX(), input_.GetMouseY());
        }

        if ((event_.Type == sf::Event::KeyPressed) && (event_.Key.Code == sf::Key::V))
        {
            mapper_->addEnemy(gamelogic::FAST_ENEMY, input_.GetMouseX(), input_.GetMouseY());
        }

        if ((event_.Type == sf::Event::KeyPressed) && (event_.Key.Code == sf::Key::A))
        {
            mapper_->addTower(gamelogic::MORTAR_TOWER, input_.GetMouseX(), input_.GetMouseY());
        }

        if ((event_.Type == sf::Event::KeyPressed) && (event_.Key.Code == sf::Key::S))
        {
            mapper_->addTower(gamelogic::ARROW_TOWER, input_.GetMouseX(), input_.GetMouseY());
        }

        if ((event_.Type == sf::Event::KeyPressed) && (event_.Key.Code == sf::Key::D))
        {
            mapper_->addTower(gamelogic::ICE_TOWER, input_.GetMouseX(), input_.GetMouseY());
        }

        if ((event_.Type == sf::Event::KeyPressed) && (event_.Key.Code == sf::Key::F))
        {
            mapper_->addTower(gamelogic::SPECIAL_TOWER, input_.GetMouseX(), input_.GetMouseY());
        }
        // Mouse button left pressed
        if ((event_.Type == sf::Event::MouseButtonPressed) && (event_.MouseButton.Button == sf::Mouse::Left))
        {
            //mapper->addTower(gamelogic::MORTAR_TOWER, Input.GetMouseX(), Input.GetMouseY());
        }

        // Mouse button right pressed
        if ((event_.Type == sf::Event::MouseButtonPressed) && (event_.MouseButton.Button == sf::Mouse::Right))
        {
            mapper_->addTower(gamelogic::SPECIAL_TOWER, event_.MouseButton.X, event_.MouseButton.Y);
        }
    }
}

} // IOHandling
