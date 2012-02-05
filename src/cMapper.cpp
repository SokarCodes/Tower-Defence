#include <iostream>
#include <vector>
#include "cGameEntity.h"
#include "cMapper.h"

cMapper* cMapper::thisPointer_ = NULL;
bool cMapper::instanceFlag_ = false;

cMapper* cMapper::getInstance() {
    if (!instanceFlag_)
    {
        thisPointer_ = new cMapper();
        instanceFlag_ = true;
        return thisPointer_;
    }
    else
    {
        return thisPointer_;
    }
}

void cMapper::add(cGameEntity *ent) {
    entityContainer_.push_back(ent);
    std::cout << "Added cGameEntity: " << ent->name() << " to container!\n";
}

void cMapper::showEntities() {
    std::vector<cGameEntity*>::iterator iter = entityContainer_.begin();
    std::cout << "mapper contains: ";
    for (;iter < entityContainer_.end();iter++)
        std::cout << (*iter)->name() << ", ";
    std::cout << "\n";
}

void cMapper::update(float frametime) {
    std::vector<cGameEntity*>::iterator iter = entityContainer_.begin();

    for (;iter < entityContainer_.end();iter++)
        (*iter)->update(frametime);
}

cGameEntity* cMapper::getTarget() {
    std::vector<cGameEntity*>::iterator iter = entityContainer_.begin();

    for (;iter < entityContainer_.end();iter++)
        if ((*iter)->name() == "Enemy")
            return (*iter);
    return NULL;
}

void cMapper::deleteInstance(cGameEntity *instance) {
    std::vector<cGameEntity*>::iterator iter = entityContainer_.begin();
    for (;iter < entityContainer_.end();iter++)
        if ((*iter) == instance)
            entityContainer_.erase(iter);
}
