
#include <gorn/asset/FileLoader.hpp>

namespace gorn
{

    FileLoader::~FileLoader()
    {
    }

    bool FileLoader::validate(const std::string& name) const NOEXCEPT
    {
        return true;
    }

}
