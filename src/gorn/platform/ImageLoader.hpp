#ifndef __gorn__ImageLoader__
#define __gorn__ImageLoader__

#include <memory>

namespace gorn
{
	class Image;
    class Data;

	class ImageLoader
	{
    public:
		virtual ~ImageLoader(){};

        /**
         * The stream should be at the start
         *
         * @return true if the image can be loaded
         */
        virtual bool validate(const Data& data) const
        {
            return true;
        }

        /**
         * The stream should be at the start
         * @return the new asset
         */
        virtual std::unique_ptr<Image> load(const Data& data) const = 0;
	};
}

#endif
