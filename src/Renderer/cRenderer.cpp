#include <iostream>
#include "cRenderer.h"

namespace renderer {

bool cRenderer::instanceFlag_ = false;
cRenderer* cRenderer::thisPointer_ = NULL;

cRenderer* cRenderer::getInstance()
{
    if (instanceFlag_)
    {
        return thisPointer_;
    }
    else
    {
        thisPointer_ = new cRenderer();
        instanceFlag_ = true;
        return thisPointer_;
    }
}

void cRenderer::update(float frametime)
{
    // All rendering updates here!
}
}
