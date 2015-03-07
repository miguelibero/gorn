#ifndef __gorn__AssetLoader__
#define __gorn__AssetLoader__

#include <string>
#include <gorn/base/Config.hpp>

namespace gorn
{
    template<typename T>
	class AssetLoader
	{
    public:
		virtual ~AssetLoader(){};

        /**
         * @return true if the asset can be loaded
         */
        virtual bool validate(const std::string& name) const NOEXCEPT
        {
            return true;
        }

        /**
         * @return the loaded asset
         */
        virtual T load(const std::string& name) const = 0;
	};
}

#endif
