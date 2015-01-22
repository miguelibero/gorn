
#ifndef __gorn__Application__
#define __gorn__Application__

namespace gorn
{
	class Application
	{
	public:
	    Application();
	    void load();
	    void unload();
	    void background();
	    void foreground();
	    void update(double dt);
	};
}

#endif
