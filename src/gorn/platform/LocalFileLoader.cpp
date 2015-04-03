
#include <gorn/platform/LocalFileLoader.hpp>
#include <gorn/base/String.hpp>
#include <gorn/base/Exception.hpp>
#include <buffer.hpp>
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

    buffer LocalFileLoader::load(const std::string& name) const
    {
        auto path = getPath(name);
        FILE *fh = nullptr;
#ifdef GORN_PLATFORM_WINDOWS
		if(fopen_s(&fh, path.c_str(), "rb") != 0)
		{
			fh = nullptr;
		}
#else
        fh = fopen(path.c_str(), "rb");
#endif
		if (fh == nullptr)
        { 
            throw Exception("Could not open file.");
        } 
        fseek(fh, 0, SEEK_END);
        size_t size = ftell(fh);
        fseek(fh, 0, SEEK_SET);
        buffer buffer(size);
        if (size != fread(buffer.data(), 1, size, fh)) 
        { 
            fclose(fh);
            throw Exception("Could not read file.");
        } 
        fclose(fh);
        return buffer;
    }
}
