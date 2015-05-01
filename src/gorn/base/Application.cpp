
#include <gorn/base/Application.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    Application::Application():
    _size(480, 320), _name("GORN"),
    _drawInterval(0.0),
    _preferredFramesPerSecond(60),
    _framesPerSecond(0.0),
    _loaded(false),
    _needsReload(false)
    {
    }

    Application::~Application()
    {
    }

    void Application::setPreferredFramesPerSecond(size_t fps)
    {
        _preferredFramesPerSecond = fps;
    }

    size_t Application::getPreferredFramesPerSecond() const
    {
        return _preferredFramesPerSecond;
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
        if(_preferredFramesPerSecond == 0.0)
        {
            _framesPerSecond = 1.0/dt;
            draw();
        }
        else
        {
            _drawInterval += dt;
            auto frameDuration = 1.0/_preferredFramesPerSecond;
            if(_drawInterval > frameDuration)
            {
                draw();
                auto oldDrawInterval = _drawInterval;
                while(_drawInterval > frameDuration)
                {
                    _drawInterval -= frameDuration;
                }
                _framesPerSecond = 1.0/(oldDrawInterval-_drawInterval);
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
