
#include <gorn/base/String.hpp>

namespace gorn
{
    const size_t String::npos = -1;

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

    std::vector<std::string> String::split(const std::string& str,
        const std::string& sep, size_t max)
    {
        std::vector<std::string> parts;
        size_t pos = 0;
        while(max==npos || parts.size() < max)    
        {
            size_t end = str.find(sep, pos);
            if(end == std::string::npos)
            {
                break;
            }
            parts.push_back(str.substr(pos, end));
            pos = end+sep.size();
        }
        parts.push_back(str.substr(pos));
        return parts;
    }

    void String::trim(std::string& str, const std::string& chars)
    {
    }


}

