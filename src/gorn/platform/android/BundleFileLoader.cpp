
#include <gorn/platform/android/BundleFileLoader.hpp>
#include <jniobject/JniObject.hpp>
#include <gorn/base/Data.hpp>
#include <gorn/base/String.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{

	JniObject getJniObject()
	{
		static JniObject obj = JniObject::findSingleton("net.gorn.PlatformBridge");
		return obj;
	}

    BundleFileLoader::BundleFileLoader(const std::string& pathTemplate):
    _pathTemplate(pathTemplate)
    {
    }

    std::string BundleFileLoader::getPath(const std::string& name) const
    {
        std::string path(_pathTemplate);
        String::replaceAll(path, kPlaceholder, name);
        return path;
    }

    bool BundleFileLoader::validate(const std::string& name) const
    {
		try
		{
            auto path = getPath(name);
			return getJniObject().call("validateFile", false, path);
		}
		catch(JniException e)
		{
			throw Exception(std::string("Error validating asset '")+name+"': "+e.what());
		}
    }

    Data BundleFileLoader::load(const std::string& name) const
    {
		try
		{
            auto path = getPath(name);
			return Data(getJniObject().call("loadFile", Data(), path));
		}
		catch(JniException e)
		{
			throw Exception(std::string("Error loading file '")+name+"': "+e.what());
		}
    }



}
