
#include <X11/X.h>
#include <X11/XKBlib.h>
#include <X11/Xlib.h>
#include <gorn/base/Application.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/gl/Base.hpp>
#include <GL/glx.h>
#include <GL/glew.h>
#include <sys/time.h>
#include <iostream>

int main(void)
{
    Window root;
    GLint att[] = { GLX_RGBA,
        GLX_DEPTH_SIZE, 24,
        GLX_DOUBLEBUFFER,
        GLX_STENCIL_SIZE, 8,
        None };
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
    int x11Fd = ConnectionNumber(display);
    XWindowAttributes gwa;
    XEvent xev;

    Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(display, window, &wmDeleteMessage, 1);

    app->realLoad();

    bool buttonPressed = false;
    bool buttonPressEnded = false;

    while(!finished)
    {
        struct timeval lastTime(currTime);
        gettimeofday(&currTime, NULL);
        FD_ZERO(&inFds);
        FD_SET(x11Fd, &inFds);

        XGetWindowAttributes(display, window, &gwa);
        glViewport(0, 0, gwa.width, gwa.height);

        double dt = ((double)currTime.tv_sec - lastTime.tv_sec)
            + ((double)currTime.tv_usec-lastTime.tv_usec)/(1000000.0);

        app->realUpdate(dt);

        while(XPending(display))
        {
            XNextEvent(display, &xev);
            glm::vec2 p;
            switch( xev.type )
            {
            case FocusIn:
                app->realForeground();
                break;
            case FocusOut:
                app->realBackground();
                break;
            case ClientMessage:
                if ((Atom)xev.xclient.data.l[0] == wmDeleteMessage)
                {
                    finished = true;
                }
                break;
            case ButtonPress:
                p = glm::vec2(xev.xbutton.x, xev.xbutton.y);
                buttonPressed = true;
                break;
            case MotionNotify: 
                p = glm::vec2(xev.xmotion.x, xev.xmotion.y);
                break;
            case ButtonRelease:
                p = glm::vec2(xev.xmotion.x, xev.xmotion.y);
                buttonPressEnded = true;
                p = glm::vec2(xev.xmotion.x, xev.xmotion.y);
                break;
            }
            if(buttonPressed)
            {               
                p.y = app->getSize().y - p.y;
                p = (p/app->getSize())*2.0f-glm::vec2(1.0f);
                if(buttonPressEnded)
                {
                    app->realTouchEnd(p);
                    buttonPressed = false;
                    buttonPressEnded = false;
                }
                else
                {
                    app->realTouch(p);
                }
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
