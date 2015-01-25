
#ifndef __gorn__AssetFileLoader__
#define __gorn__AssetFileLoader__

#include <gorn/asset/FileLoader.hpp>

class JniObject;

namespace gorn
{
    class AssetFileLoader : public FileLoader
    {
    private:
        static const char* kPlaceholder;

        std::string _pathTemplate;
        std::string getPath(const std::string& name) const;
        static JniObject& getJniObject();
    public:
        AssetFileLoader(const std::string& pathTemplate=kPlaceholder);
        bool validate(const std::string& name) const;
        Data load(const std::string& name) const;
    };
}

#endif