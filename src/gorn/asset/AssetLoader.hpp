#ifndef __gorn__AssetLoader__
#define __gorn__AssetLoader__

namespace gorn
{
    class Data;

    template<typename T>
	class AssetLoader
	{
    public:
		virtual ~AssetLoader(){};

        /**
         * @return true if the asset can be loaded
         */
        virtual bool validate(const Data& data) const
        {
            return true;
        }

        /**
         * @return the asset to be loaded
         */
        virtual T load(Data&& data) const = 0;
	};
}

#endif
