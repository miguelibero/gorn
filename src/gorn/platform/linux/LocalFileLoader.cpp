
#include <gorn/platform/linux/LocalFileLoader.hpp>
#include <gorn/base/Data.hpp>
#include <gorn/base/String.hpp>
#include <sys/stat.h>

namespace gorn {

    LocalFileLoader::LocalFileLoader(const std::string& pathTemplate):
    _pathTemplate(pathTemplate)
    {
    }

    std::string LocalFileLoader::getPath(const std::string& name) const
    {
        std::string path(_pathTemplate);
        String::replaceAll(path, "%s", name);
        return path;
    }

    bool LocalFileLoader::validate(const std::string& name) const
    {
        auto path = getPath(name);
        struct stat buffer;   
        return (stat (path.c_str(), &buffer) == 0); 
    }

    Data loadLocalFile(const std::string& path)
    {
        return Data::readFile(path);
    }

    std::future<Data> LocalFileLoader::load(const std::string& name) const
    {
        return std::async(std::launch::async, &loadLocalFile, getPath(name));
    }
}
