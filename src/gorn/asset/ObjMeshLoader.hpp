#ifndef __gorn__ObjMeshLoader__
#define __gorn__ObjMeshLoader__

#include <gorn/asset/DataAssetLoader.hpp>

namespace gorn
{
    class Mesh;

	class ObjMeshLoader : public DataAssetLoader<Mesh>
	{
    public:
        ObjMeshLoader();
        bool validate(const Data& data) const;
        Mesh load(Data&& data) const;
	};
}

#endif
