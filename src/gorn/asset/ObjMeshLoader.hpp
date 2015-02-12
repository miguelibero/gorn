#ifndef __gorn__ObjMeshLoader__
#define __gorn__ObjMeshLoader__

#include <gorn/asset/DataAssetLoader.hpp>

namespace gorn
{
    class RenderCommand;

	class ObjMeshLoader : public DataAssetLoader<RenderCommand>
	{
    public:
        ObjMeshLoader();
        bool validate(const Data& data) const;
        RenderCommand load(Data&& data) const;
	};
}

#endif
