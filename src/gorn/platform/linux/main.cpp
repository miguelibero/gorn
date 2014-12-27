#include <GLFW/glfw3.h>
#include <gorn/base/Application.hpp>

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
	gorn::Application app;
    GLFWwindow* window;

    if (!glfwInit())
    {
        return -1;
    }

    window = glfwCreateWindow(GORN_WINDOW_WIDTH, GORN_WINDOW_HEIGHT, GORN_WINDOW_TITLE, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    app.load();

    double appTime = glfwGetTime();

    while (!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();

        double nextTime = glfwGetTime();
        app.update(nextTime - appTime);
        appTime = nextTime;
    }

    app.unload();

    glfwTerminate();
    return 0;
}