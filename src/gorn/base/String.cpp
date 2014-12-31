
#include <gorn/base/String.hpp>

namespace gorn
{
    size_t String::replaceAll(std::string& str,
        const std::string& from, const std::string& to)
    {
        size_t found = 0;
        for(size_t pos = 0; ; pos += to.length())
        {
            pos = str.find(from, pos);
            if( pos == std::string::npos)
            {
                break;
            }
            str.erase(pos, from.length());
            str.insert(pos, to);
            found++;
        }
        return found;
	};

}

