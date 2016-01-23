
#ifndef __gorn__Application__
#define __gorn__Application__

#include <memory>
#include <string>
#include <glm/glm.hpp>

namespace gorn
{
    class Application
    {
    private:
        glm::vec2 _size;
        std::string _name;
        double _drawInterval;
        size_t _preferredFramesPerSecond;
        double _framesPerSecond;
        bool _loaded;
        bool _needsReload;
    protected:
        virtual void load();
        virtual void reload();
        virtual void unload();
        virtual void background();
        virtual void foreground();
        virtual void update(double dt);
        virtual void draw();
        virtual void resize();
        virtual void touch(const glm::vec2& p);
        virtual void touchEnd(const glm::vec2& p);

        void setName(const std::string& name);
    public:
        Application();
        virtual ~Application();
       
        void setSize(const glm::vec2& size);
        const glm::vec2& getSize();
        const std::string& getName();

        void setPreferredFramesPerSecond(size_t fps);
        size_t getPreferredFramesPerSecond() const;
        double getFramesPerSecond() const;

        void realLoad();
        void realUnload();
        void realForeground();
        void realBackground();
        bool realUpdate(double dt);
        void realTouch(const glm::vec2& p);
        void realTouchEnd(const glm::vec2& p);
    };

    std::unique_ptr<Application> main();
}

#endif
