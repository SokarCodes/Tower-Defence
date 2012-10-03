#include "GLESv2context.h"
#include "X11window.h"
#include <X11/Xlib.h>
#include <iostream>

namespace renderer
{

GLESv2Context::GLESv2Context() :
    majorVersion(0),
    minorVersion(0),
    eglDisplay(0),
    eglSurface(0),
    eglConfig(0),
    numConfigs(0),
    eglContext(0)

{
}

void GLESv2Context::bindWindow(X11Window *window)
{
    xWin = window;
    xWin->setRendercontext(this);
}

void GLESv2Context::init()
{
    EGLint configAttributes[] =
    {
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE
    };

    EGLint contextAttributes[] =
    {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE
    };

    Display *xDisplay = xWin->getDisplay();
    Window xWindow =xWin->getWindow();

    // Get EGL display and initialize it.
    eglDisplay = eglGetDisplay( xDisplay );
    if (eglDisplay == EGL_NO_DISPLAY)
    {
        std::cout << "EGL: GetDisplay failed!\n";
        //return EGL_FALSE;
    }
    if (!eglInitialize(eglDisplay, &majorVersion, &minorVersion))
    {
        std::cout << "EGL: Initialize failed!\n";
        //return EGL_FALSE;
    }
    std::cout << "EGL version: " << majorVersion << "." << minorVersion << "\n";

    // Let EGL choose best configuration
    if (!eglChooseConfig(eglDisplay, configAttributes, &eglConfig, 1, &numConfigs))
    {
        std::cout << "EGL: No suitable configuration found!\n";
    }

    // Get EGL surface
    eglSurface = eglCreateWindowSurface(eglDisplay, eglConfig, xWindow, NULL);
    if (eglSurface == EGL_NO_SURFACE)
    {
        switch(eglGetError())
        {
        case EGL_BAD_MATCH:
            std::cout << "Bad match!\n";
            break;
        case EGL_BAD_CONFIG:
            std::cout << "Bad config!\n";
            break;
        case EGL_BAD_NATIVE_WINDOW:
            std::cout << "Bad native window!\n";
            break;
        case EGL_BAD_ALLOC:
            std::cout << "Bad alloc!\n";
            break;
        }
    }

    eglContext = eglCreateContext(eglDisplay, eglConfig, EGL_NO_CONTEXT, contextAttributes);
    if (eglContext == EGL_NO_CONTEXT)
    {
        EGLint error = eglGetError();
        switch(error)
        {
        case EGL_BAD_CONFIG:
            std::cout << "EGL: Bad Config!\n";
            break;
        case EGL_BAD_ATTRIBUTE:
            std::cout << "EGL: Bad attribute!\n";
            break;
        default:
            std::cout << "EGL: Context error!\n";
        }

        //return EGL_FALSE;
    }
    eglMakeCurrent(eglDisplay, eglSurface, eglSurface,eglContext);
}

void GLESv2Context::refresh()
{
    // Trigger a buffer swap
    eglSwapBuffers(eglDisplay, eglSurface);

    // Clear the buffers for the next frame.
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

} // namespace renderer
