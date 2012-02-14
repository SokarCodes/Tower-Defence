/*
 * File:   main.cpp
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 8:02 PM
 */
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "GameLogic/cGameEntity.h"
#include "GameLogic/cMapper.h"
#include "GameLogic/entityEnums.h"
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
/*
 * 
 */
int main(int argc, char** argv)
{
    cout << "Hello tower defense - experimental branch!\n";

    bool appRunning = true;
    
    // Initialize variables for gameloop timer logic
    sf::Clock clock;
    const int framerate = 60;
    float framestartTime = 0; //fix this
    float difference = 0;
    float sleepTime = 0;
    float frameBudget = 1/(float)framerate;

    // Create SFML renderwindow
    sf::RenderWindow window(sf::VideoMode(800,600,32), "Tower-Defence!", sf::Style::Close);

    // Create event mapper
    sf::Event Event;

    // Testing renderwindow draw shapes and text
    sf::Shape towerShape = sf::Shape::Circle(0.f, 0.f, 5.f, sf::Color::White);
    sf::Shape enemyShape = sf::Shape::Rectangle(0.f, 0.f, 10.f, 10.f, sf::Color(255,255,200,200));
    sf::String text("Frametime");


    // Inputmapper
    const sf::Input& Input = window.GetInput();

    // Singleton mapper class which updates all gameEntities
    gamelogic::cMapper *mapper;

    try {
        mapper = gamelogic::cMapper::getInstance();
    } catch (bad_alloc&) {
        return EXIT_FAILURE;
    }

    // Start running the clock just before gameloop
    clock.Reset();

    // Gameloop
    while(appRunning)
    {
        window.Clear();

        std::ostringstream frametimer;
        std::ostringstream towers, enemies;
        frametimer << framestartTime;
        std::string buffer;
        buffer.append("Frametime: ").append(frametimer.str());

        std::vector<gamelogic::cGameEntity*> enemyList = mapper->getEnemyEntities();
        enemies << enemyList.size();
        buffer.append("\nEnemies: ").append(enemies.str());
        std::vector<gamelogic::cGameEntity*>::iterator iter = enemyList.begin();
        for (;iter < enemyList.end(); iter++)
        {
            enemyShape.SetPosition((*iter)->getXPosition(), (*iter)->getYPosition());
            if ((*iter)->name() == "Walking_enemy")
                enemyShape.SetColor(sf::Color::Magenta);
            else if ((*iter)->name() == "Flying_enemy")
                enemyShape.SetColor(sf::Color::Blue);
            else if ((*iter)->name() == "Invisible_enemy")
                enemyShape.SetColor(sf::Color::Green);
            else if ((*iter)->name() == "Fast_enemy")
                enemyShape.SetColor(sf::Color::Red);
            window.Draw(enemyShape);
        }
        std::vector<gamelogic::cGameEntity*> towerList = mapper->getTowerEntities();
        towers << towerList.size();
        buffer.append(", Towers: ").append(towers.str());
        iter = towerList.begin();
        text.SetText(buffer);
        for (;iter < towerList.end(); iter++)
        {
            towerShape.SetPosition((*iter)->getXPosition(), (*iter)->getYPosition());
            if ((*iter)->name() == "Mortar_tower")
                towerShape.SetColor(sf::Color::Cyan);
            else if ((*iter)->name() == "Arrow_tower")
                towerShape.SetColor(sf::Color::White);
            else if ((*iter)->name() == "Ice_tower")
                towerShape.SetColor(sf::Color::Yellow);
            else if ((*iter)->name() == "Special_tower")
                towerShape.SetColor(sf::Color(100,50,220,200));
            window.Draw(towerShape);
        }


        window.Draw(text);
        window.Display();


        // Get current framestart time
        framestartTime = clock.GetElapsedTime();

        // Update game logic. Here only mapper->update()
        mapper->update(framestartTime);

        // Get time elapsed in game logic update
        difference = clock.GetElapsedTime() - framestartTime;

        // If difference is smaller than budgeted, rest until next frame
        if (difference < frameBudget)
        {
            // Rendering budgets:
            // 60fps = 16,667ms
            // 30fps = 33,333ms
            // 10fps = 100ms
            //  5fps = 200ms
            sleepTime = frameBudget - difference;
            // Sleep for rest of the frame
            sf::Sleep(sleepTime);
        }

        // Event loop checker
        while (window.GetEvent(Event))
        {
            // Window closed
            if (Event.Type == sf::Event::Closed)
            {
                cout << "User interrupt close window!\n";
                appRunning = false;
                window.Close();
            }

            // Escape key pressed
            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))
            {
                cout << "User interrupt ESC-key!\n";
                appRunning = false;
                window.Close();
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Z))
            {
                mapper->addEnemy(gamelogic::WALKING_ENEMY, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::X))
            {
                mapper->addEnemy(gamelogic::FLYING_ENEMY, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::C))
            {
                mapper->addEnemy(gamelogic::INVISIBLE_ENEMY, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::V))
            {
                mapper->addEnemy(gamelogic::FAST_ENEMY, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::A))
            {
                mapper->addTower(gamelogic::MORTAR_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::S))
            {
                mapper->addTower(gamelogic::ARROW_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::D))
            {
                mapper->addTower(gamelogic::ICE_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }

            if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::F))
            {
                mapper->addTower(gamelogic::SPECIAL_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }
            // Mouse button left pressed
            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Left))
            {
                //mapper->addTower(gamelogic::MORTAR_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }

            // Mouse button right pressed
            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Right))
            {
                //mapper->addTower(gamelogic::SPECIAL_TOWER, Input.GetMouseX(), Input.GetMouseY());
            }
        }
    }
    // End of gameloop. Destroy mapper.
    delete mapper;

    return EXIT_SUCCESS;
}

