#include <iostream>
#include "cMapper.h"

cMapper* cMapper::thisPointer = NULL;
bool cMapper::instanceFlag = false;

cMapper* cMapper::getInstance() {
    if (!instanceFlag)
    {
        thisPointer = new cMapper();
        instanceFlag = true;
        return thisPointer;
    }
    else
    {
        return thisPointer;
    }
}

void cMapper::add(gameEntity *ent) {
    entityContainer.push_back(ent);
    std::cout << "Added gameEntity: " << ent->name() << " to container!\n";
}

void cMapper::showEntities() {
    std::vector<gameEntity*>::iterator iter = entityContainer.begin();
    std::cout << "mapper contains: ";
    for (;iter < entityContainer.end();iter++)
        std::cout << (*iter)->name() << ", ";
    std::cout << "\n";
}

void cMapper::update() {
    std::vector<gameEntity*>::iterator iter = entityContainer.begin();

    for (;iter < entityContainer.end();iter++)
        (*iter)->update();
}

gameEntity* cMapper::getTarget() {
    std::vector<gameEntity*>::iterator iter = entityContainer.begin();

    for (;iter < entityContainer.end();iter++)
        if ((*iter)->name() == "Enemy")
            return (*iter);
}

void cMapper::deleteInstance(gameEntity *instance) {
    std::vector<gameEntity*>::iterator iter = entityContainer.begin();
    for (;iter < entityContainer.end();iter++)
        if ((*iter) == instance)
            entityContainer.erase(iter);
}
