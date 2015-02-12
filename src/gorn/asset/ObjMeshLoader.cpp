

#include <gorn/asset/ObjMeshLoader.hpp>
#include <gorn/render/RenderCommand.hpp>
#include <gorn/render/Kinds.hpp>
#include <gorn/base/Data.hpp>
#include <gorn/base/String.hpp>
#include <string>

namespace gorn
{
    const char* kElementPrefix = "f";
    const char* kComponentSeparator = " ";
    const char* kFaceSeparator = "/";
    const char  kCommentPrefix = '#';

    const std::map<std::string,std::string> kAttrPrefixes = {
        {"v",  AttributeKind::Position},
        {"vt", AttributeKind::TexCoords},
        {"vn", AttributeKind::Normal}
    };

    const std::vector<std::string> kFaceComponents = {
        AttributeKind::Position,
        AttributeKind::TexCoords,
        AttributeKind::Normal
    };

    ObjMeshLoader::ObjMeshLoader()
    {
    }

    bool ObjMeshLoader::validate(const Data& data) const
    {
        return true;
    }

    RenderCommand ObjMeshLoader::load(Data&& data) const
    {
        DataInputStream in(data);
        std::string line;

        std::map<std::string, std::vector<float>> attrData;
        std::map<std::string, std::vector<unsigned>> elmData;
        while(in.read(line) > 0)
        {
            if(line.find(kCommentPrefix) == 0)
            {
                continue;
            }
            auto parts = String::split(line, kComponentSeparator);
            if(parts.empty())
            {
                continue;
            }
            auto itr = kAttrPrefixes.find(parts.at(0));
            if(itr != kAttrPrefixes.end())
            {
                auto& type = itr->second;
                for(auto itr = parts.begin()+1; itr != parts.end(); ++itr)
                {
                    attrData[type].push_back(
                        String::convertTo<float>(*itr));
                }
            }
            else if(parts.at(0) == kElementPrefix)
            {
                for(auto itr = parts.begin()+1; itr != parts.end(); ++itr)
                {
                    auto fparts = String::split(*itr, kFaceSeparator);
                    for(size_t i=0; i < fparts.size()
                        && i < kFaceComponents.size(); ++i)
                    {
                        elmData[kFaceComponents[i]].push_back(
                            String::convertTo<unsigned>(fparts[i])-1);
                    }
                }
            }
        }
        RenderCommand cmd;

        for(auto itr = attrData.begin(); itr != attrData.end(); ++itr)
        {
            cmd.withAttribute(itr->first, std::move(itr->second),
                3, BasicType::Float);
        }
        for(auto itr = elmData.begin(); itr != elmData.end(); ++itr)
        {
            cmd.withElements(itr->first, std::move(itr->second),
                BasicType::UnsignedInteger);
        }

        return cmd;
    }
}
