
#include <gorn/base/Application.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    Application::Application():
    _size(480, 320), _name("GORN")
    {
    }

    Application::~Application()
    {
    }

    const glm::vec2& Application::getSize()
    {
        return _size;
    }

    void Application::setSize(const glm::vec2& size)
    {
        _size = size;
    }

    void Application::setName(const std::string& name)
    {
        _name = name;
    }

    const std::string& Application::getName()
    {
        return _name;
    }

    void Application::load()
    {
    }

    void Application::unload()
    {
    }

    void Application::background()
    {
    }

    void Application::foreground()
    {
    }

    void Application::update(double dt)
    {
    }

    void Application::draw()
    {
    }

    void Application::touch(const glm::vec2& p)
    {
    }

    void Application::realLoad()
    {
        load();
    }

    void Application::realUnload()
    {
        unload();
    }

    void Application::realForeground()
    {
        foreground();
    }

    void Application::realBackground()
    {
        background();
    }

    void Application::realUpdate(double dt)
    {
        update(dt);
        draw();
    }

    void Application::realTouch(const glm::vec2& p)
    {
        touch(p);
    }
}
