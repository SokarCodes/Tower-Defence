/* 
 * File:   gameEntity.h
 * Author: juginabi
 *
 * Created on January 24, 2012, 8:25 PM
 */
#include <iostream>
#ifndef GAMEENTITY_H
#define	GAMEENTITY_H
class enemyEntity;

class gameEntity {
public:
    virtual ~gameEntity() { std::cout << "gameEntity destruction!" << std::endl; }
    void setPosition(int x, int y) {this->x_coord = x; this->y_coord = y; }
    virtual void update() = 0;
    virtual void setDamage(const unsigned int) {}
    virtual void setRange(const unsigned int) {}
    virtual void setTarget(gameEntity*) {}
private:
    int x_coord;
    int y_coord;
};


#endif	/* GAMEENTITY_H */

