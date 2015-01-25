
#include <gorn/platform/android/AssetFileLoader.hpp>
#include <jniobject/JniObject.hpp>
#include <gorn/base/Data.hpp>
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

    AssetFileLoader::AssetFileLoader(const std::string& pathTemplate):
    _pathTemplate(pathTemplate)
    {
    }

    std::string AssetFileLoader::getPath(const std::string& name) const
    {
        std::string path(_pathTemplate);
        String::replaceAll(path, kPlaceholder, name);
        return path;
    }

    bool AssetFileLoader::validate(const std::string& name) const
    {
		try
		{
            auto path = getPath(name);
			return getJniObject().call("validateFile", false, path);
		}
		catch(const JniException& e)
		{
			throw Exception(std::string("JNI Error validating asset '")+name+"': "+e.what());
		}
    }

    Data AssetFileLoader::load(const std::string& name) const
    {
		try
		{
            auto path = getPath(name);
			return Data(getJniObject().call("loadFile", std::vector<uint8_t>(), path));
		}
		catch(const JniException& e)
		{
			throw Exception(std::string("JNI Error loading file '")+name+"': "+e.what());
		}
    }



}
