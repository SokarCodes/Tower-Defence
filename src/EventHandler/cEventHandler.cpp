#include <iostream>
#include "cEventHandler.h"

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

void cEventHandler::update()
{
    // Update method
}
