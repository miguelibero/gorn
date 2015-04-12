

#include <gorn/asset/ObjMeshLoader.hpp>
#include <gorn/asset/Mesh.hpp>
#include <gorn/render/RenderKinds.hpp>
#include <gorn/base/String.hpp>
#include <gorn/base/Exception.hpp>
#include <buffer.hpp>
#include <buffer_reader.hpp>
#include <string>
#include <algorithm>

namespace gorn
{
    const char* kFacePrefix = "f";
    const char* kPositionPrefix = "v";
    const char* kNormalPrefix = "vn";
    const char* kTexCoordPrefix = "vt";
    const char* kComponentSeparator = " ";
    const char* kFaceSeparator = "/";
    const char  kCommentPrefix = '#';

    ObjMeshLoader::ObjMeshLoader() NOEXCEPT
    {
    }

    bool ObjMeshLoader::validate(const buffer& data) const NOEXCEPT
    {
        return !data.binary();
    }

    Mesh ObjMeshLoader::load(const buffer& data) const
    {
        buffer_reader in(data);
        std::string line;

        Mesh mesh;
        while(in.read(line) > 0)
        {
            String::trim(line, " \t\r");
            if(line.find(kCommentPrefix) == 0)
            {
                continue;
            }
            auto parts = String::split(line, kComponentSeparator);
            parts.erase(std::remove_if(parts.begin(), parts.end(),
                [](const std::string& part){
                    return part.empty();
                }), parts.end());
            if(parts.empty())
            {
                continue;
            }
            if(parts.at(0) == kPositionPrefix)
            {
                if(parts.size() < 4)
                {
                    throw Exception("Position should contain 3 floats");
                }
                mesh.addPosition(glm::vec3(
                    String::convertTo<float>(parts[1]),
                    String::convertTo<float>(parts[2]),
                    String::convertTo<float>(parts[3])
                ));
            }
            else if(parts.at(0) == kNormalPrefix)
            {
                if(parts.size() < 4)
                {
                    throw Exception("Normal should contain 3 floats");
                }
                mesh.addNormal(glm::vec3(
                    String::convertTo<float>(parts[1]),
                    String::convertTo<float>(parts[2]),
                    String::convertTo<float>(parts[3])
                ));
            }
            else if(parts.at(0) == kTexCoordPrefix)
            {
                if(parts.size() < 3)
                {
                    throw Exception("Texture should contain 2 floats");
                }
                mesh.addTexCoord(glm::vec2(
                    String::convertTo<float>(parts[1]),
                    String::convertTo<float>(parts[2])
                ));
            }
            else if(parts.at(0) == kFacePrefix)
            {
                std::vector<Mesh::Element> elms;
                for(auto itr = parts.begin()+1; itr != parts.end(); ++itr)
                {
                    auto fsparts = String::split(*itr, kFaceSeparator);
                    std::vector<MeshElement::elm_t> fparts;
                    fparts.reserve(fsparts.size());
                    for(auto& part : fsparts)
                    {
                        fparts.push_back(
                            String::convertTo<MeshElement::elm_t>(part)-1);
                    }
                    Mesh::Element elm;
                    if(fparts.size() > 0)
                    {
                        elm.position = fparts[0];
                    }
                    if(fparts.size() > 1)
                    {
                        elm.texCoord = fparts[1];
                    }
                    if(fparts.size() > 2)
                    {
                        elm.normal = fparts[2];
                    }
                    elms.push_back(std::move(elm));
                }
                if(elms.size() == 4)
                {
                    // convert quad to 2 tris
                    mesh.addElement(elms.at(0));
                    mesh.addElement(elms.at(1));
                    mesh.addElement(elms.at(2));
                    mesh.addElement(elms.at(2));
                    mesh.addElement(elms.at(3));
                    mesh.addElement(elms.at(0));
                }
                else if(elms.size() == 3)
                {
                    mesh.addElement(elms.at(0));
                    mesh.addElement(elms.at(1));
                    mesh.addElement(elms.at(2));
                }
                else
                {
                    throw Exception("Face should contain 3 or 4 elements");
                }
            }
        } 
        return mesh;
    }
}
