
#include <gorn/platform/android/AssetFileLoader.hpp>
#include <JniObject.hpp>
#include <buffer.hpp>
#include <gorn/base/String.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    JniObject& AssetFileLoader::getJniObject()
    {
        static JniObject obj = JniObject::findSingleton("me.ibero.gorn.NativeBridge");
        return obj;
    }

    const char* AssetFileLoader::kPlaceholder = "%s";

    AssetFileLoader::AssetFileLoader(const std::string& pathTemplate) NOEXCEPT:
    _pathTemplate(pathTemplate)
    {
    }

    std::string AssetFileLoader::getPath(const std::string& name) const NOEXCEPT
    {
        std::string path(_pathTemplate);
        String::replaceAll(path, kPlaceholder, name);
        return path;
    }

    bool AssetFileLoader::validate(const std::string& name) const NOEXCEPT
    {
        try
        {
            auto path = getPath(name);
            return getJniObject().call("validateFile", false, path);
        }
        catch(const JniException& e)
        {
            return false;
        }
    }

    buffer AssetFileLoader::load(const std::string& name) const
    {
        try
        {
            auto path = getPath(name);
            return buffer(getJniObject().call("loadFile", std::vector<uint8_t>(), path));
        }
        catch(const JniException& e)
        {
            throw Exception(std::string("JNI Error loading file '")+name+"': "+e.what());
        }
    }



}
