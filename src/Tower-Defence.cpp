/* 
 * File:   main.cpp
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 23, 2012, 8:02 PM
 */
#include <iostream>
#include <cstdlib>
#include <sstream>
#include "cGameEntity.h"
#include "cTowerEntity.h"
#include "cEnemyEntity.h"
#include "cMapper.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

using namespace std;
/*
 * 
 */
int main(int argc, char** argv) {

    /// Just testing classes
    cout << "Hello tower defense!\n";

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

    // Testing renderwindow drawText
    sf::String Text("DERP!");
    Text.SetFont(sf::Font::GetDefaultFont());

    // Inputmapper
    const sf::Input& Input = window.GetInput();

    // Singleton mapper class which updates all gameEntities
    cMapper *mapper;

    try {
        mapper = cMapper::getInstance();
    } catch (bad_alloc&) {
        return EXIT_FAILURE;
    }

    std::vector<sf::Shape> circleVector;
    std::vector<sf::Shape> squareVector;

    //mapper->add(dynamic_cast<cGameEntity*> (new cEnemyEntity));

    // Start running the clock just before gameloop
    clock.Reset();

    // Gameloop
    while(appRunning)
    {
        window.Clear();
        window.Draw(Text);
        std::vector<sf::Shape>::iterator iter1 = circleVector.begin();
        for (;iter1 < circleVector.end(); iter1++)
            window.Draw((*iter1));
        std::vector<sf::Shape>::iterator iter2 = squareVector.begin();
        for (;iter2 < squareVector.end(); iter2++)
            window.Draw((*iter2));
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

            // Mouse button left pressed
            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Left))
            {
                mapper->add(dynamic_cast<cGameEntity*> (new cTowerEntity(Input.GetMouseX(),Input.GetMouseY())));
                sf::Shape Circle = sf::Shape::Circle(0.f, 0.f, 5.f, sf::Color::White);
                Circle.SetPosition(Input.GetMouseX(),Input.GetMouseY());
                circleVector.push_back(Circle);

            }

            // Mouse button right pressed
            if ((Event.Type == sf::Event::MouseButtonPressed) && (Event.Key.Code == sf::Mouse::Right))
            {
                mapper->add(dynamic_cast<cGameEntity*> (new cEnemyEntity(Input.GetMouseX(),Input.GetMouseY())));
                sf::Shape Square = sf::Shape::Rectangle(0.f, 0.f, 10.f, 10.f, sf::Color::Blue);
                Square.SetPosition(Input.GetMouseX(),Input.GetMouseY());
                circleVector.push_back(Square);

            }
            // Check how many entities are there left on map.
            int towers, enemies = 0;
            std::string buffer;
            towers = mapper->getTowerCount();
            enemies = mapper->getEnemyCount();
            std::ostringstream ostr;
            std::ostringstream estr;
            ostr << towers;
            estr << enemies;
            buffer.append("Towers: ").append(ostr.str()).append(" Enemies: ").append(estr.str());
            Text.SetText(buffer);
        }
    }
    // Target has been acquired on last update so now fire sequence initiates.
    delete mapper;

    return EXIT_SUCCESS;
}

