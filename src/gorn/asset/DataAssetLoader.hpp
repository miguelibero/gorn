#ifndef __gorn__DataAssetLoader__
#define __gorn__DataAssetLoader__

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
        virtual bool validate(const Data& data) const
        {
            return true;
        }

        /**
         * @return the loaded asset
         */
        virtual T load(Data&& data) const = 0;
	};
}

#endif
