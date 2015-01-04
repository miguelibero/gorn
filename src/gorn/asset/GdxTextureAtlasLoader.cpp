
#include <gorn/asset/GdxTextureAtlasLoader.hpp>
#include <gorn/asset/TextureAtlas.hpp>
#include <gorn/base/String.hpp>
#include <gorn/base/Data.hpp>

namespace gorn {

    GdxTextureAtlasLoader::GdxTextureAtlasLoader()
    {
    }
    
    bool GdxTextureAtlasLoader::validate(const Data& data) const
    {
        return true;
    }

    TextureAtlas GdxTextureAtlasLoader::load(Data&& data) const
    {
        TextureAtlas atlas;
        std::string line;
        DataInputStream input(data);

        // texture name
        while(line.empty() && !input.reachedEnd())
        {
            input.readLine(line);
            String::trim(line);
        }
        atlas.setTexture(line);

        bool inRegion = false;
        TextureRegion region;
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
                    region = TextureRegion();
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
                    if(n == "rotate" && v == "true")
                    {
                        region.rotate();
                    }
                    else if(n == "xy")
                    {
                        sep = v.find(',');                       
                        region.origin.x = std::stoi(v.substr(0, sep));
                        region.origin.y = std::stoi(v.substr(sep+1));
                    }
                    else if(n == "size")
                    {
                        sep = v.find(',');
                        region.size.x = std::stoi(v.substr(0, sep));
                        region.size.y = std::stoi(v.substr(sep+1));
                    }
                    else if(n == "orig")
                    {
                        sep = v.find(',');
                        region.original.x = std::stoi(v.substr(0, sep));
                        region.original.y = std::stoi(v.substr(sep+1));
                    }
                    else if(n == "offset")
                    {
                        sep = v.find(',');
                        region.offset.x = std::stoi(v.substr(0, sep));
                        region.offset.y = std::stoi(v.substr(sep+1));
                    }
                    else if(n == "index")
                    {
                        regionIndex = std::stoi(v);
                    }
                }
                else
                {
                    atlas.setRegion(regionName, region, regionIndex);
                    region = TextureRegion();
                    regionName = line;
                }             
            }
        }

        return atlas;
    }

}
