#ifndef CX11WINDOW_H
#define CX11WINDOW_H

#include "X11/Xlib.h"

namespace renderer
{
class GLESv2Context;

class X11Window
{
public:
    // Default constructor
    X11Window();

    // Destructor
    ~X11Window();

    // Opens X11 renderwindow and makes proper setup
    void open();

    // Return display pointer
    Display* getDisplay();

    // Return window X11 window pointer
    Window& getWindow();

    // Setup render context for this window.
    void setRendercontext(GLESv2Context* context) { eglContext = context; }

    // Refresh context and window.
    void refresh();
private:
    // GLES2 rendercontext
    GLESv2Context* eglContext;

    // xDisplay pointer
    Display *xDisplay;

    // XWindow pointer
    Window xWindow;
};
}
#endif // CX11WINDOW_H
