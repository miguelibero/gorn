
#include <gorn/asset/GdxSpriteAtlasLoader.hpp>
#include <gorn/asset/SpriteAtlas.hpp>
#include <gorn/base/String.hpp>
#include <gorn/base/Data.hpp>
#include <gorn/render/MaterialManager.hpp>

namespace gorn {

    GdxSpriteAtlasLoader::GdxSpriteAtlasLoader(MaterialManager& materials):
    _materials(materials)
    {
    }
    
    bool GdxSpriteAtlasLoader::validate(const Data& data) const
    {
        return true;
    }

    SpriteAtlas GdxSpriteAtlasLoader::load(Data&& data) const
    {
        SpriteAtlas atlas;
        std::string line;
        DataInputStream input(data);

        // texture name
        while(line.empty() && !input.reachedEnd())
        {
            input.readLine(line);
            String::trim(line);
        }
        atlas.setMaterial(_materials.load(line));

        bool inRegion = false;
        SpriteRegion region;
        std::string regionName;
        size_t regionIndex = 0;

        while(!input.reachedEnd())
        {
            input.readLine(line);
            std::size_t sep = line.find(':');
            std::string n = line.substr(0, sep);
            std::string v = line.substr(sep+1);

            if(!inRegion)
            {
                if(sep == std::string::npos)
                {
                    inRegion = true;
                    region = SpriteRegion();
                    regionName = line;
                }
                else
                {
                    // header value
                }
            }
            else
            {
                if(line.substr(0, 1) == " ")
                {
                    String::trim(n);
                    String::trim(v);
                    if(n == "rotate")
                    {
                        region.setRotate(v == "true");
                    }
                    else if(n == "xy")
                    {
                        sep = v.find(',');                       
                        region.setOrigin(
                            String::convertTo<int>(v.substr(0, sep)),
                            String::convertTo<int>(v.substr(sep+1)));
                    }
                    else if(n == "size")
                    {
                        sep = v.find(',');
                        region.setSize(
                            String::convertTo<int>(v.substr(0, sep)),
                            String::convertTo<int>(v.substr(sep+1)));
                    }
                    else if(n == "orig")
                    {
                        sep = v.find(',');
                        region.setOriginalSize(
                            String::convertTo<int>(v.substr(0, sep)),
                            String::convertTo<int>(v.substr(sep+1)));
                    }
                    else if(n == "offset")
                    {
                        sep = v.find(',');
                        region.setOffset(
                            String::convertTo<int>(v.substr(0, sep)),
                            String::convertTo<int>(v.substr(sep+1)));
                    }
                    else if(n == "index")
                    {
                        regionIndex = String::convertTo<int>(v);
                    }
                }
                else
                {
                    atlas.setRegion(regionName, region, regionIndex);
                    region = SpriteRegion();
                    regionName = line;
                }             
            }
        }

        return atlas;
    }

}
