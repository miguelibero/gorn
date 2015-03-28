#ifndef __gorn__Exception__
#define __gorn__Exception__

#include <string>
#include <exception>
#ifdef GORN_PLATFORM_ANDROID
#include <android/log.h>
#endif

namespace gorn
{
	class Exception: public std::exception
	{
	private:
		std::string _msg;
	public:
		Exception(const std::string& msg):
		_msg(msg)
		{
#ifdef GORN_PLATFORM_ANDROID
            __android_log_print(ANDROID_LOG_ERROR, "gorn",
                "exception: %s", msg.c_str());
#endif
		}

		virtual const char* what() const throw()
		{
			return _msg.c_str();
		}
	};
}

#endif /* defined(__gorn__Exception__) */
