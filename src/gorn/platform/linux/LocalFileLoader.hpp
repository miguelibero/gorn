
#ifndef __gorn__LocalFileLoader__
#define __gorn__LocalFileLoader__

#include <gorn/asset/FileLoader.hpp>

namespace gorn {

    class LocalFileLoader : public FileLoader
    {
    private:
        std::string _pathTemplate;
        std::string getPath(const std::string& name) const;
    public:
        LocalFileLoader(const std::string& pathTemplate);
        bool validate(const std::string& name) const;
        Data load(const std::string& name) const;
    };
}

#endif
