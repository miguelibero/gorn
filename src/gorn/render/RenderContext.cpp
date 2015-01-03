#include <gorn/render/RenderContext.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/asset/Image.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{
    const char* RenderContext::kDefaultTextureTag = "tex";
    const char* RenderContext::kDefaultVertexShaderTag = "vsh";
    const char* RenderContext::kDefaultFragmentShaderTag = "fsh";

    RenderContext::RenderContext():
    _files(std::make_shared<FileManager>()),
    _images(std::make_shared<AssetManager<Image>>(_files))
    {
    }

    void RenderContext::setFileManager(const std::shared_ptr<FileManager>& mng)
    {
        _files = mng;
    }

    void RenderContext::setImageManager(const std::shared_ptr<AssetManager<Image>>& mng)
    {
        _images = mng;
    }

    const std::shared_ptr<FileManager>& RenderContext::getFileManager() const
    {
        return _files;
    }

    const std::shared_ptr<AssetManager<Image>>& RenderContext::getImageManager() const
    {
        return _images;
    }

    std::shared_ptr<Texture> RenderContext::loadTexture(const std::string& name)
    {
        auto itr = _textures.find(name);
        if(itr != _textures.end())
        {
            return itr->second;
        }
        auto& def = defineTexture(name);
        if(_images == nullptr)
        {
            throw Exception("Image asset manager not set.");
        }
        auto img = _images->load(def.getImageTag(), def.getImageName()).get();
        auto tex = std::make_shared<Texture>(def.getTarget());
        for(auto itr = def.getIntParameters().begin();
            itr != def.getIntParameters().end(); ++itr)
        {
            tex->setParameter(itr->first, itr->second);
        }
        for(auto itr = def.getFloatParameters().begin();
            itr != def.getFloatParameters().end(); ++itr)
        {
            tex->setParameter(itr->first, itr->second);
        }
        for(auto itr = def.getIntPointerParameters().begin();
            itr != def.getIntPointerParameters().end(); ++itr)
        {
            tex->setParameter(itr->first, itr->second);
        }
        for(auto itr = def.getFloatPointerParameters().begin();
            itr != def.getFloatPointerParameters().end(); ++itr)
        {
            tex->setParameter(itr->first, itr->second);
        }
        tex->setImage(img, def.getLevelOfDetail());
        _textures.insert(itr, {name, tex});
        return tex;
    }

    std::shared_ptr<Shader> RenderContext::loadShader(const std::string& name, ShaderType type)
    {
        auto& shaders = _shaders[type];
        auto itr = shaders.find(name);
        if(itr != shaders.end())
        {
            return itr->second;
        }
        if(_files == nullptr)
        {
            throw Exception("File manager not set.");
        }
        std::string tag;
        if(type == ShaderType::Vertex)
        {
            tag = kDefaultVertexShaderTag;
        }
        else if(type == ShaderType::Fragment)
        {
            tag = kDefaultFragmentShaderTag;
        }
        auto data = _files->load(tag, name).get();
        auto shader = std::make_shared<Shader>(data, type);
        shaders.insert(itr, {name, shader});
        return shader;
    }

    std::shared_ptr<Program> RenderContext::loadProgram(const std::string& name)
    {
        auto itr = _programs.find(name);
        if(itr != _programs.end())
        {
            return itr->second;
        }
        auto& def = defineProgram(name);
        auto vertex = loadShader(def.getVertexShader(), ShaderType::Vertex);
        auto fragment = loadShader(def.getFragmentShader(), ShaderType::Fragment);

        auto program = std::make_shared<Program>(fragment, vertex);
        for(auto& name : def.getAttributes())
        {
            program->getAttribute(name);
        }
        for(auto& name : def.getUniforms())
        {
            program->getUniform(name);
        }
        _programs.insert(itr, {name, program});
        return program;
    }

    std::shared_ptr<Material> RenderContext::loadMaterial(const std::string& name)
    {
        auto itr = _materials.find(name);
        if(itr != _materials.end())
        {
            return itr->second;
        }
        auto& def = defineMaterial(name);
        auto program = loadProgram(def.getProgram());

        auto material = std::make_shared<Material>(program);
        for(auto itr = def.getTextures().begin();
            itr != def.getTextures().end(); ++itr)
        {
            material->setTexture(itr->first, loadTexture(itr->second));
        }
        for(auto itr = def.getUniformValues().begin();
            itr != def.getUniformValues().end(); ++itr)
        {
            material->setUniformValue(itr->first, itr->second);
        }

        _materials.insert(itr, {name, material});
        return material;
    }

    ProgramDefinition& RenderContext::defineProgram(const std::string& name)
    {
        auto itr = _programDefinitions.find(name);
        if(itr == _programDefinitions.end())
        {
            itr = _programDefinitions.insert(itr, {name, ProgramDefinition()});
            itr->second.withShader(name);
        }
        return itr->second;
    }

    MaterialDefinition& RenderContext::defineMaterial(const std::string& name)
    {
        auto itr = _materialDefinitions.find(name);
        if(itr == _materialDefinitions.end())
        {
            itr = _materialDefinitions.insert(itr, {name, MaterialDefinition()});
            itr->second.withProgram(name);
        }
        return itr->second;
    }


    TextureDefinition& RenderContext::defineTexture(const std::string& name)
    {
        auto itr = _textureDefinitions.find(name);
        if(itr == _textureDefinitions.end())
        {
            itr = _textureDefinitions.insert(itr, {name, TextureDefinition()});
            itr->second.withImage(name).withImageTag(kDefaultTextureTag);
        }
        return itr->second;
    }

    void RenderContext::drawArrays(const VertexArray& vao, GLsizei size, GLint offset)
	{
		vao.bind();
		glDrawArrays(GL_TRIANGLES, offset, size);
	}

    void RenderContext::drawElements(const VertexArray& vao, GLsizei size, GLenum type, GLint offset)
    {
        vao.activate();
		glDrawElements(GL_TRIANGLES, size, type,
            reinterpret_cast<const GLvoid*>(offset));
    }

}
