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
            switch (event_.Key.Code)
            {
            case sf::Key::Escape:
                std::cout << "User interrupt ESC-key!\n";
                appRunning = false;
                render_->getRenderwindow()->Close();
                break;
            case sf::Key::Z:
                mapper_->addEnemy(gamelogic::WALKING_ENEMY, input_.GetMouseX(), input_.GetMouseY());
                break;
            case sf::Key::X:
                mapper_->addEnemy(gamelogic::FLYING_ENEMY, input_.GetMouseX(), input_.GetMouseY());
                break;
            case sf::Key::C:
                mapper_->addEnemy(gamelogic::INVISIBLE_ENEMY, input_.GetMouseX(), input_.GetMouseY());
                break;
            case sf::Key::V:
                mapper_->addEnemy(gamelogic::FAST_ENEMY, input_.GetMouseX(), input_.GetMouseY());
                break;
            case sf::Key::A:
                mapper_->addTower(gamelogic::MORTAR_TOWER, input_.GetMouseX(), input_.GetMouseY());
                break;
            case sf::Key::S:
                mapper_->addTower(gamelogic::ARROW_TOWER, input_.GetMouseX(), input_.GetMouseY());
                break;
            case sf::Key::D:
                mapper_->addTower(gamelogic::ICE_TOWER, input_.GetMouseX(), input_.GetMouseY());
                break;
            case sf::Key::F:
                mapper_->addTower(gamelogic::SPECIAL_TOWER, input_.GetMouseX(), input_.GetMouseY());
                break;
            default:
                std::cout << "No action for key.\n";
            }
            break;
            // Mouse button pressed
        case sf::Event::MouseButtonPressed:
            switch (event_.MouseButton.Button)
            {
            case sf::Mouse::Left:
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
            break;
        case sf::Event::MouseMoved:
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
