#ifndef __gorn__ImageLoader__
#define __gorn__ImageLoader__

#include <future>

namespace gorn
{
	class Image;
    class Data;

	class ImageLoader
	{
    public:
		virtual ~ImageLoader(){};

        /**
         * @return true if the image can be loaded
         */
        virtual bool validate(const Data& data) const
        {
            return true;
        }

        /**
         * @return the new image
         */
        virtual std::future<Image> load(Data&& data) const = 0;
	};
}

#endif
