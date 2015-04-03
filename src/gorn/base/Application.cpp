
#include <gorn/base/Application.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    Application::Application():
    _size(480, 320), _name("GORN"),
    _drawInterval(0.0),
    _maxFramesPerSecond(60),
    _framesPerSecond(0.0),
    _loaded(false),
    _needsReload(false)
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

    void Application::reload()
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
        if(_loaded)
        {
            reload();
        }
        else
        {
            _loaded = true;
            load();
        }
    }

    void Application::realUnload()
    {
        if(_loaded)
        {
            _loaded = false;
            unload();
        }
    }

    void Application::realForeground()
    {
        if(!_loaded)
        {
            return;
        }
#ifdef GORN_PLATFORM_ANDROID
        _needsReload = true;
#endif
        foreground();
    }

    void Application::realBackground()
    {
        if (!_loaded)
        {
            return;
        }
        background();
    }

    void Application::realUpdate(double dt)
    {
        if (!_loaded)
        {
            return;
        }
        if(_needsReload)
        {
            _needsReload = false;
            reload();
        }
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
        if (!_loaded)
        {
            return;
        }
        touch(p);
    }
}
