#ifndef RENDERER_H
#define RENDERER_H

#include "SFML/Graphics.hpp"
#include "../GameLogic/cMapper.h"

namespace renderer {

class cRenderer
{
public:
    /// Destructor, sets instanceFlag to false so getInstance creates new on request
    ~cRenderer() {instanceFlag_ = false;}

    /// Returns singleton pointer
    static cRenderer* getInstance();

    /// Get renderwindow for inputmapper
    sf::RenderWindow* getRenderwindow();

    void update(float);

    void drawFPS(float spentTime);
private:
    /// Private constructor because singleton instance is gotten from getInstance()
    cRenderer();

    /// Status for singleton instance pointer
    static bool instanceFlag_;

    /// Pointer to this singleton class
    static cRenderer* thisPointer_;

    /// Renderwindow
    sf::RenderWindow *window_;

    /// GameLogic pointer
    static gamelogic::cMapper* mapper_;

    sf::String *text_;

    sf::Shape *enemyShape_;
    sf::Shape *towerShape_;
    sf::Shape *projectile_;


};


}
#endif
