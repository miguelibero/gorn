
#include <X11/X.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <gorn/base/Application.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/render/Gl.hpp>
#include <GL/glx.h>

#ifndef GORN_WINDOW_WIDTH
#define GORN_WINDOW_WIDTH 640
#endif

#ifndef GORN_WINDOW_HEIGHT
#define GORN_WINDOW_HEIGHT 480
#endif

#ifndef GORN_WINDOW_TITLE
#define GORN_WINDOW_TITLE "GORN"
#endif

int main(void)
{
    Window root;
    GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
    XVisualInfo *vi;
    Colormap cmap;
    XSetWindowAttributes swa;
    Display* display;
    Window window;
    GLXContext glxContext;
    bool finished = false;
    gorn::Application app;

    display = XOpenDisplay(NULL);

    if(display == NULL)
    {
        throw gorn::Exception("cannot connect to X server");
    }
    
    root = DefaultRootWindow(display);
    vi = glXChooseVisual(display, 0, att);

    if(vi == NULL)
    {
        throw gorn::Exception("no appropriate visual found");
    }

    cmap = XCreateColormap(display, root, vi->visual, AllocNone);
    swa.colormap = cmap;
    swa.event_mask = ExposureMask | KeyPressMask | PointerMotionMask | ButtonPressMask | ButtonReleaseMask;
    window = XCreateWindow(display, root, 0, 0, GORN_WINDOW_WIDTH, GORN_WINDOW_HEIGHT, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    XMapWindow(display, window);
    XStoreName(display, window, GORN_WINDOW_TITLE);
    glxContext = glXCreateContext(display, vi, NULL, GL_TRUE);
    glXMakeCurrent(display, window, glxContext);

    fd_set inFds;
    struct timeval tv;
    tv.tv_usec = 1000000.0f/60;
    tv.tv_sec = 0;
    int x11Fd = ConnectionNumber(display);
    XWindowAttributes gwa;
    XEvent xev;

    app.load();

    while(!finished)
    {
        struct timeval otv(tv);
        FD_ZERO(&inFds);
        FD_SET(x11Fd, &inFds);
        select(x11Fd+1, &inFds, 0, 0, &tv);

        XGetWindowAttributes(display, window, &gwa);
        glViewport(0, 0, gwa.width, gwa.height);

        app.update(0.0f);

        while(XPending(display))
        {
            XNextEvent(display, &xev);
        }

        glXSwapBuffers(display, window);
    }

    app.unload();
    glXMakeCurrent(display, None, NULL);
    glXDestroyContext(display, glxContext);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}