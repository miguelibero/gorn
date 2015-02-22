#ifndef __gorn__String__
#define __gorn__String__

#include <string>
#include <vector>

namespace gorn
{
	class String
	{
	public:
        static const char* kWhitespaceChars;
        static const char* kTagSeparator;
        static const char* kDefaultTag;
        static const size_t npos;

   		String() = delete;

        static size_t replaceAll(std::string& str,
            const std::string& from, const std::string& to);

        static std::vector<std::string> split(const std::string& str,
            const std::string& sep, size_t max=npos);

        template<typename V>
        static std::vector<V> splitConvert(const std::string& str,
            const std::string& sep, size_t max=npos);

        static void trim(std::string& str, const std::string& chrs=kWhitespaceChars);
        static void ltrim(std::string& str, const std::string& chrs=kWhitespaceChars);
        static void rtrim(std::string& str, const std::string& chrs=kWhitespaceChars);

        template<typename V>
        static V convertTo(const std::string& value);

        static std::pair<std::string,std::string> splitTag(const std::string& str);
        static bool addTag(std::string& str, const std::string& tag);
	};

    template<typename V>
    std::vector<V> String::splitConvert(const std::string& str,
        const std::string& sep, size_t max)
    {
        auto sparts = split(str, sep, max);
        std::vector<V> parts;
        parts.reserve(sparts.size());
        for(auto& part : sparts)
        {
            parts.push_back(String::convertTo<V>(part));
        }
        return parts;
    }

}

#endif
