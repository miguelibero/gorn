
#include <X11/X.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <gorn/base/Application.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/render/Gl.hpp>
#include <GL/glx.h>
#include <GL/glew.h>
#include <sys/time.h>

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
    auto app = gorn::main();

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
    window = XCreateWindow(display, root, 0, 0, app->getSize().x, app->getSize().y, 0, vi->depth, InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
    XMapWindow(display, window);
    XStoreName(display, window, app->getName().c_str());
    glxContext = glXCreateContext(display, vi, NULL, GL_TRUE);
    glXMakeCurrent(display, window, glxContext);

    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        throw gorn::Exception(reinterpret_cast<const char*>(glewGetErrorString(err)));
    }

    fd_set inFds;
    struct timeval currTime;
    gettimeofday(&currTime, NULL);
    struct timeval frameRate;
    frameRate.tv_usec = 1000000.0f/60;
    frameRate.tv_sec = 0;
    int x11Fd = ConnectionNumber(display);
    XWindowAttributes gwa;
    XEvent xev;

    app->realLoad();

    while(!finished)
    {
        struct timeval lastTime(currTime);
        gettimeofday(&currTime, NULL);
        FD_ZERO(&inFds);
        FD_SET(x11Fd, &inFds);
        select(x11Fd+1, &inFds, 0, 0, &frameRate);

        XGetWindowAttributes(display, window, &gwa);
        glViewport(0, 0, gwa.width, gwa.height);

        double dt = ((double)currTime.tv_sec - lastTime.tv_sec)
            + ((double)currTime.tv_usec-lastTime.tv_usec)/(1000*1000);

        app->realUpdate(dt);

        while(XPending(display))
        {
            XNextEvent(display, &xev);
            switch( xev.type )
            {
            case FocusIn:
                app->realForeground();
                break;
            case FocusOut:
                app->realBackground();
                break;
            case ButtonPress:
                glm::vec2 p(xev.xbutton.x, xev.xbutton.y);
                p.y = app->getSize().y - p.y;
                p = (p/app->getSize())*2.0f-glm::vec2(1.0f);
                app->realTouch(p);
                break;
            }
        }

        glXSwapBuffers(display, window);
    }

    app->realUnload();
    glXMakeCurrent(display, None, NULL);
    glXDestroyContext(display, glxContext);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
}
