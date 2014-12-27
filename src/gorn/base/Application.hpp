
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
	    void update(double dt);
	};
}

#endif /* defined(__gorn__Application__) */