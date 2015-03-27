
#include <gorn/base/Application.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    Application::Application():
    _size(480, 320), _name("GORN"),
    _drawInterval(0.0),
    _maxFramesPerSecond(60),
    _framesPerSecond(0.0)
    {
    }

    Application::~Application()
    {
    }

    void Application::setMaxFramesPerSecond(size_t fps)
    {
        _maxFramesPerSecond = fps;
    }

    size_t Application::getMaxFramesPerSecond() const
    {
        return _maxFramesPerSecond;
    }

    double Application::getFramesPerSecond() const
    {
        return _framesPerSecond;
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
        if(_maxFramesPerSecond == 0.0)
        {
            _framesPerSecond = 1.0/dt;
            draw();
        }
        else
        {
            _drawInterval += dt;
            auto frameDuration = 1.0/_maxFramesPerSecond;
            if(_drawInterval > frameDuration)
            {
                _framesPerSecond = 1.0/_drawInterval;
                draw();
                while(_drawInterval > frameDuration)
                {
                    _drawInterval -= frameDuration;
                }
            }
        }
    }

    void Application::realTouch(const glm::vec2& p)
    {
        touch(p);
    }
}
