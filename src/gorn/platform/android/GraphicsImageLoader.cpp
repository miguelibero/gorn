
#include <gorn/platform/android/GraphicsImageLoader.hpp>
#include <jniobject/JniObject.hpp>
#include <gorn/base/Exception.hpp>
#include <gorn/asset/Image.hpp>

namespace gorn
{

	JniObject& GraphicsImageLoader::getJniObject()
	{
		static JniObject obj = JniObject::findSingleton("me.ibero.gorn.NativeBridge");
		return obj;
	}

    bool GraphicsImageLoader::validate(const Data& input) const
    {
        return true;
    }

    Image GraphicsImageLoader::load(Data&& input) const
    {
		try
		{
			auto data = Data(getJniObject().call("loadImage",
                std::vector<uint8_t>(), input.mem()));
            if(data.empty())
            {
    			throw Exception("Could not decode image data.");        
            }
            auto info = getJniObject().call("getImageInfo", std::vector<int>());
            GLenum format = info[2] ? GL_RGBA : GL_RGB;
			return Image(std::move(data), info[0], info[1], format, GL_UNSIGNED_BYTE);
		}
		catch(JniException e)
		{
			throw Exception(std::string("Error loading image: ")+e.what());
		}
	}

}
