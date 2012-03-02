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
    input_(render_->getRenderwindow()->GetInput()),
    mouseleftDown_(false),
    entity_(0)
{

}

void cEventHandler::update()
{
    sf::Vector2f inputCoord;

    // Event loop checker
    while (render_->getRenderwindow()->GetEvent(event_))
    {
        switch (event_.Type)
        {
        // Window closed
        case sf::Event::Closed:
            std::cout << "User interrupt close window!\n";
            appRunning = false;
            render_->getRenderwindow()->Close();
            break;
            // Keyboard key pressed
        case sf::Event::KeyPressed:
            inputCoord.x = input_.GetMouseX();
            inputCoord.y = input_.GetMouseY();
            switch (event_.Key.Code)
            {
            case sf::Key::Escape:
                std::cout << "User interrupt ESC-key!\n";
                appRunning = false;
                render_->getRenderwindow()->Close();
                break;
            case sf::Key::Z:
                mapper_->addEnemy(gamelogic::WALKING_ENEMY, inputCoord);
                break;
            case sf::Key::X:
                mapper_->addEnemy(gamelogic::FLYING_ENEMY, inputCoord);
                break;
            case sf::Key::C:
                mapper_->addEnemy(gamelogic::INVISIBLE_ENEMY, inputCoord);
                break;
            case sf::Key::V:
                mapper_->addEnemy(gamelogic::FAST_ENEMY, inputCoord);
                break;
            case sf::Key::A:
                mapper_->addTower(gamelogic::MORTAR_TOWER, inputCoord);
                break;
            case sf::Key::S:
                mapper_->addTower(gamelogic::ARROW_TOWER, inputCoord);
                break;
            case sf::Key::D:
                mapper_->addTower(gamelogic::ICE_TOWER, inputCoord);
                break;
            case sf::Key::F:
                mapper_->addTower(gamelogic::SPECIAL_TOWER, inputCoord);
                break;
            default:
                std::cout << "No action for key.\n";
            }
            break;
            // Mouse button pressed
        case sf::Event::MouseButtonPressed:
            inputCoord.x = input_.GetMouseX();
            inputCoord.y = input_.GetMouseY();
            switch (event_.MouseButton.Button)
            {
            case sf::Mouse::Left:
                mouseleftDown_ = true;
                mapper_->addEnemy(gamelogic::WALKING_ENEMY, inputCoord);
                std::cout << "Mouse left!\n";
                break;
            case sf::Mouse::Right:
                std::cout << "Mouse right!\n";
                break;
            case sf::Mouse::Middle:
                std::cout << "Mouse middle!\n";
                break;
            default:
                std::cout << "No action for mousebutton.\n";
            }
            break;
        case sf::Event::Resized:
            break;
        case sf::Event::LostFocus:
            break;
        case sf::Event::GainedFocus:
            break;
        case sf::Event::TextEntered:
            break;
        case sf::Event::KeyReleased:
            break;
        case sf::Event::MouseWheelMoved:
            switch (event_.MouseWheel.Delta)
            {
            case -1:
                std::cout << "Mouse wheen down.\n";
                break;
            case 1:
                std::cout << "Mouse wheen up.\n";
                break;
            }
            break;
        case sf::Event::MouseButtonReleased:
            mouseleftDown_ = false;
            break;
        case sf::Event::MouseMoved:
            inputCoord.x = input_.GetMouseX();
            inputCoord.y = input_.GetMouseY();
            if (mouseleftDown_)
            {
                entity_ = gamelogic::cMapper::getInstance()->getTarget(inputCoord, 50);
                if (entity_)
                {
                    std::cout << "Setting entity position: " << inputCoord.x << "," << inputCoord.y << ".\n";
                    entity_->setPosition(inputCoord);
                }
            }
            else
            {
               gamelogic::cMapper::getInstance()->deleteEntity(entity_);
               entity_ = 0;
            }
            break;
        case sf::Event::MouseEntered:
            break;
        case sf::Event::MouseLeft:
            // This event is already handled in mousebuttonPressed
            break;
        case sf::Event::Count:
            break;
        case sf::Event::JoyButtonPressed:
            break;
        case sf::Event::JoyButtonReleased:
            break;
        case sf::Event::JoyMoved:
            break;
        }
    }
}

} // IOHandling
