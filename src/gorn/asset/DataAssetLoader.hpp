#ifndef __gorn__DataAssetLoader__
#define __gorn__DataAssetLoader__

#include <gorn/base/Config.hpp>

namespace gorn
{
    class Data;

    template<typename T>
	class DataAssetLoader
	{
    public:
		virtual ~DataAssetLoader(){};

        /**
         * @return true if the asset can be loaded
         */
        virtual bool validate(const Data& data) const NOEXCEPT
        {
            return true;
        }

        /**
         * @return the loaded asset
         */
        virtual T load(const Data& data) const = 0;
	};
}

#endif
