
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
    protected:
	    virtual void load();
	    virtual void unload();
	    virtual void background();
	    virtual void foreground();
	    virtual void update(double dt);
	    virtual void draw();
        virtual void touch(const glm::vec2& p);

        void setSize(const glm::vec2& size);
        void setName(const std::string& name);
	public:
	    Application();
        virtual ~Application();
        
        const glm::vec2& getSize();
        const std::string& getName();

        void realLoad();
        void realUnload();
        void realForeground();
        void realBackground();
        void realUpdate(double dt);
        void realTouch(const glm::vec2& p);
	};

    std::unique_ptr<Application> main();
}

#endif
