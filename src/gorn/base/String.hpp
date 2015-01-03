#ifndef __gorn__String__
#define __gorn__String__

#include <string>
#include <vector>

namespace gorn
{
	class String
	{
	private:
		String();

	public:
        static const size_t npos;

        static size_t replaceAll(std::string& str,
            const std::string& from, const std::string& to);

        static std::vector<std::string> split(const std::string& str,
            const std::string& sep, size_t max=npos);

        static void trim(std::string& str, const std::string& chars=" \t\r\n");
	};

}

#endif
