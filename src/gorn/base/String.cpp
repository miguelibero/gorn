
#include <gorn/base/String.hpp>
#include <cstdlib>
#include <sstream>
#include <algorithm>

namespace gorn
{
    const size_t String::npos = -1;
    const char* String::kWhitespaceChars = " \t\r\n";
    const char* String::kTagSeparator = ":";
    const char* String::kDefaultTag = "default";

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
            parts.push_back(str.substr(pos, end-pos));
            pos = end+sep.size();
        }
        parts.push_back(str.substr(pos));
        return parts;
    }

    std::pair<std::string,std::string> String::splitTag(const std::string& str)
    {
        auto parts = split(str, kTagSeparator, 2);
        std::string name(str);
        std::string tag(String::kDefaultTag);
        if(parts.size() > 1)
        {
            tag = parts.front();
            name = parts.back();
        }
        return std::make_pair(tag, name);
    }

    bool String::addTag(std::string& str, const std::string& prefix)
    {
        std::string sep(kTagSeparator);
        auto parts = String::split(str, sep, 2);
        if(parts.size() == 1)
        {
            str = prefix+sep+str;
            return true;
        }
        return false;
    }

    void String::ltrim(std::string& str, const std::string& chrs)
    {
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [&chrs](const char chr){
            return chrs.find(chr) == std::string::npos;
        }));
    }

    void String::rtrim(std::string& str, const std::string& chrs)
    {
        str.erase(std::find_if(str.rbegin(), str.rend(), [&chrs](const char chr){
            return chrs.find(chr) == std::string::npos;
        }).base(), str.end());
    }

    void String::trim(std::string& str, const std::string& chrs)
    {
        ltrim(str, chrs);
        rtrim(str, chrs);
    }

    template<>
    int String::convertTo(const std::string& value)
    {
        return atoi(value.c_str());
    }

    template<>
    unsigned int String::convertTo(const std::string& value)
    {
        std::istringstream reader(value);
        unsigned int val;
        reader >> val;
        return val;
    }

    template<>
    short String::convertTo(const std::string& value)
    {
        return atoi(value.c_str());
    }

    template<>
    float String::convertTo(const std::string& value)
    {
        float f;
#ifdef GORN_PLATFORM_WINDOWS
        sscanf_s(value.c_str(), "%f", &f);
#else
        sscanf(value.c_str(), "%f", &f);
#endif
        return f;
    }

    template<>
    double String::convertTo(const std::string& value)
    {
        return strtod(value.c_str(), 0);
    }

    template<>
    long String::convertTo(const std::string& value)
    {
        return strtol(value.c_str(), 0, 10);
    }

    template<>
    long long String::convertTo(const std::string& value)
    {
        return strtoll(value.c_str(), 0, 10);
    }

    template<>
    unsigned long String::convertTo(const std::string& value)
    {
        return strtoul(value.c_str(), 0, 10);
    }

    template<>
    unsigned long long String::convertTo(const std::string& value)
    {
        return strtoull(value.c_str(), 0, 10);
    }

}
