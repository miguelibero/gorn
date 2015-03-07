
#include <gorn/platform/LocalFileLoader.hpp>
#include <gorn/base/Data.hpp>
#include <gorn/base/String.hpp>
#include <sys/stat.h>

namespace gorn {

    const char* LocalFileLoader::kPlaceholder = "%s";

    LocalFileLoader::LocalFileLoader(const std::string& pathTemplate) NOEXCEPT:
    _pathTemplate(pathTemplate)
    {
    }

    std::string LocalFileLoader::getPath(const std::string& name) const NOEXCEPT
    {
        std::string path(_pathTemplate);
        String::replaceAll(path, kPlaceholder, name);
        return path;
    }

    bool LocalFileLoader::validate(const std::string& name) const NOEXCEPT
    {
        auto path = getPath(name);
        struct stat buffer;   
        return (stat (path.c_str(), &buffer) == 0); 
    }

    Data LocalFileLoader::load(const std::string& name) const
    {
        auto path = getPath(name);
        return Data::readFile(path);
    }
}
