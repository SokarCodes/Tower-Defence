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
    for (;iter < entityContainer.end();iter++)
        std::cout << "mapper contains: " << (*iter)->name() << "\n";
}

