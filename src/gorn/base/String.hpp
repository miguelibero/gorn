#ifndef __gorn__String__
#define __gorn__String__

#include <string>

namespace gorn
{
	class String
	{
	private:
		String();

	public:
        static size_t replaceAll(std::string& str,
            const std::string& from, const std::string& to);		
	};

}

#endif
