#ifndef GLESv2Context_H
#define GLESv2Context_H

#include "EGL/egl.h"
#include "GLES2/gl2.h"
#include "X11window.h"

namespace renderer
{

class GLESv2Context
{
public:
    GLESv2Context();
    void init();
    void bindWindow(X11Window*);
    void refresh();
private:
    // EGL variables
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay eglDisplay;
    EGLSurface eglSurface;
    EGLConfig eglConfig;
    EGLint numConfigs;
    EGLContext eglContext;

    X11Window *xWin;

};

} // namespace renderer
#endif // CGLESv2Context_H
