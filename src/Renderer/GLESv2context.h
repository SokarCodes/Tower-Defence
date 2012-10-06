#ifndef GLESv2Context_H
#define GLESv2Context_H

#include "EGL/egl.h"
#include "GLES2/gl2.h"

namespace renderer
{
class X11Window;

class GLESv2Context
{
public:
    GLESv2Context();

    // Bind rendercontext to X11Window surface
    void bindWindow(X11Window*);

    // Refresh render buffers
    void refresh();

    /// Set background color
    void setBGcolor(float, float, float, float);
private:
    // Initialize rendering surface
    void init();

    // EGL variables
    EGLint majorVersion;
    EGLint minorVersion;
    EGLDisplay eglDisplay;
    EGLSurface eglSurface;
    EGLConfig eglConfig;
    EGLint numConfigs;
    EGLContext eglContext;

    X11Window *xWin;

    float red_;
    float green_;
    float blue_;
    float alpha_;

};

} // namespace renderer
#endif // CGLESv2Context_H
