#ifndef CX11WINDOW_H
#define CX11WINDOW_H

#include "X11/Xlib.h"

class GLESv2Context;

class X11Window
{
public:
    X11Window();
    ~X11Window();
    void open();
    Display* getDisplay();
    Window getWindow();
    void setRendercontext(GLESv2Context* context) { eglContext = context; }
    void refresh();
private:
    GLESv2Context* eglContext;
    Display *xDisplay;
    Window xWindow;
};

#endif // CX11WINDOW_H
