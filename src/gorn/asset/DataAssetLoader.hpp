#ifndef __gorn__DataAssetLoader__
#define __gorn__DataAssetLoader__

#include <gorn/base/Config.hpp>

class buffer;

namespace gorn
{
    template<typename T>
	class DataAssetLoader
	{
    public:
		virtual ~DataAssetLoader(){};

        /**
         * @return true if the asset can be loaded
         */
        virtual bool validate(const buffer& data) const NOEXCEPT
        {
            return true;
        }

        /**
         * @return the loaded asset
         */
        virtual T load(const buffer& data) const = 0;
	};
}

#endif
