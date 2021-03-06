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
        static std::vector<V> convertVector(const std::vector<std::string>& data);

        static void trim(std::string& str, const std::string& chrs=kWhitespaceChars);
        static void ltrim(std::string& str, const std::string& chrs=kWhitespaceChars);
        static void rtrim(std::string& str, const std::string& chrs=kWhitespaceChars);

        template<typename V>
        static V convertTo(const std::string& value);

        static std::pair<std::string,std::string> splitTag(const std::string& str);
        static bool addTag(std::string& str, const std::string& tag);

        static void fixPath(std::string& path);
        static void combinePath(std::string& path, const std::string& base);
    };

    template<typename V>
    std::vector<V> String::convertVector(const std::vector<std::string>& sparts)
    {
        std::vector<V> parts;
        parts.reserve(sparts.size());
        for(auto& part : sparts)
        {
            parts.push_back(convertTo<V>(part));
        }
        return parts;
    }

}

#endif
