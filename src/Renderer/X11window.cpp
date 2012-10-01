#include "X11window.h"
#include "GLESv2context.h"
#include <iostream>

X11Window::X11Window() :
    xDisplay(XOpenDisplay(0)),
    xWindow(0)
{
}

X11Window::~X11Window()
{
    XDestroyWindow(xDisplay, xWindow);
}

void X11Window::open()
{
    // Create X11 window with required attributes.
    xWindow = XCreateWindow(xDisplay                         // Pointer to the Display
                            , DefaultRootWindow(xDisplay)	// Parent Window
                            , 0                              // X of top-left corner
                            , 0              				// Y of top-left corner
                            , 640                          	// requested width
                            , 480                            // requested height
                            , 0                              // border width
                            , CopyFromParent                 // window depth
                            , CopyFromParent                 // window class - InputOutput / InputOnly / CopyFromParent
                            , CopyFromParent                 // visual type
                            , 0                              // value mask
                            , 0);                            // attributes
    // Map window to display and show it on the screen.
    XMapWindow(xDisplay, xWindow);
}

Display *X11Window::getDisplay()
{
    return xDisplay;
}

Window X11Window::getWindow()
{
    return xWindow;
}

void X11Window::refresh()
{
    eglContext->refresh();
    XFlush(xDisplay);
}
