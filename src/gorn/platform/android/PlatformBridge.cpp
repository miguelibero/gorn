
#include <gorn/platform/PlatformBridge.hpp>
#include <jniobject/JniObject.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{

	JniObject getJniObject()
	{
		static JniObject obj = JniObject::findSingleton("com.openglgame.PlatformBridge");
		return obj;
	}

	PlatformBridge::DataPtr PlatformBridge::readFile(const std::string& name)
	{
		try
		{
			auto data = new Data(getJniObject().call("readFile", Data(), name));
			return DataPtr(data);
		}
		catch(JniException e)
		{
			throw Exception(std::string("Error reading asset '")+name+"': "+e.what());
		}
	}

	ImagePtr PlatformBridge::readImage(const std::string& name)
	{
		try
		{
			auto data = new Data(getJniObject().call("readImage", Data(), name));
			return ImagePtr(data);
		}
		catch(JniException e)
		{
			throw Exception(std::string("Error reading image '")+name+"': "+e.what());
		}
	}

}