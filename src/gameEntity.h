/* 
 * File:   gameEntity.h
 * Author: Jukka Vatjus-Anttila
 *
 * Created on January 24, 2012, 8:25 PM
 */
#include <iostream>
#ifndef GAMEENTITY_H
#define	GAMEENTITY_H

class gameEntity {
public:
    virtual ~gameEntity() { std::cout << "gameEntity destruction!" << "\n"; }
    void setPosition(int x, int y) {this->x_coord = x; this->y_coord = y; }
    void getPosition() { std::cout << "X: " << this->x_coord << " Y: " << this->y_coord << "\n"; }

    virtual void update() = 0;
    virtual void setDamage(const unsigned int) {}
    virtual void setRange(const unsigned int) {}
    virtual void setTarget(gameEntity*) {}
    virtual std::string name() = 0;

private:
    int x_coord;
    int y_coord;
};


#endif	/* GAMEENTITY_H */

