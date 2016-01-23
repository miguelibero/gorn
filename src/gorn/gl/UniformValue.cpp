#include <gorn/gl/UniformValue.hpp>
#include <gorn/base/Exception.hpp>

namespace gorn
{

    template<>
    size_t UniformValue::getGlmSize<glm::vec2>()
    {
        return 2;
    }

    template<>
    size_t UniformValue::getGlmSize<glm::vec3>()
    {
        return 3;
    }

    template<>
    size_t UniformValue::getGlmSize<glm::vec4>()
    {
        return 4;
    }

    template<>
    size_t UniformValue::getGlmSize<glm::mat2>()
    {
        return 2*2;
    }

    template<>
    size_t UniformValue::getGlmSize<glm::mat3>()
    {
        return 3*3;
    }

    template<>
    size_t UniformValue::getGlmSize<glm::mat4>()
    {
        return 4*4;
    }


    UniformValue::UniformValue():
    _type(Type::Empty)
    {
    }

    UniformValue::UniformValue(GLfloat f):
    _type(Type::Float)
    {
        _float.push_back(f);
    }

    UniformValue::UniformValue(GLint i):
    _type(Type::Int)
    {
        _int.push_back(i);
    }

    UniformValue::UniformValue(const glm::vec2& v):
    _type(Type::Vector2)
    {
        addGlmObject(v);
    }

    UniformValue::UniformValue(const glm::vec3& v):
    _type(Type::Vector3)
    {
        addGlmObject(v);
    }

    UniformValue::UniformValue(const glm::vec4& v):
    _type(Type::Vector4)
    {
        addGlmObject(v);
    }

    UniformValue::UniformValue(const glm::mat2& m):
    _type(Type::Matrix2)
    {
        addGlmObject(m);
    }

    UniformValue::UniformValue(const glm::mat3& m):
    _type(Type::Matrix3)
    {
        addGlmObject(m);
    }

    UniformValue::UniformValue(const glm::mat4& m):
    _type(Type::Matrix4)
    {
        addGlmObject(m);
    }

    UniformValue::UniformValue(std::initializer_list<GLfloat> fs):
    _float(fs), _type(Type::Float)
    {
    }

    UniformValue::UniformValue(std::initializer_list<GLint> is):
    _int(is), _type(Type::Int)
    {
    }

    UniformValue::UniformValue(std::initializer_list<glm::mat2> ms):
    _type(Type::Matrix2)
    {
        for(auto& m : ms)
        {
            addGlmObject(m);
        }
    }

    UniformValue::UniformValue(std::initializer_list<glm::mat3> ms):
    _type(Type::Matrix3)
    {
        for(auto& m : ms)
        {
            addGlmObject(m);
        }
    }

    UniformValue::UniformValue(std::initializer_list<glm::mat4> ms):
    _type(Type::Matrix4)
    {
        for(auto& m : ms)
        {
            addGlmObject(m);
        }
    }

    UniformValue& UniformValue::operator=(GLfloat f)
    {
        _float = {f};
        _type = Type::Float;
        return *this;
    }

    UniformValue& UniformValue::operator=(GLint i)
    {
        _int = {i};
        _type = Type::Int;
        return *this;
    }

    UniformValue& UniformValue::operator=(const glm::vec2& v)
    {
        _float.clear();
        addGlmObject(v);
        _type = Type::Vector2;
        return *this;
    }

    UniformValue& UniformValue::operator=(const glm::vec3& v)
    {
        _float.clear();
        addGlmObject(v);
        _type = Type::Vector3;
        return *this;
    }

    UniformValue& UniformValue::operator=(const glm::vec4& v)
    {
        _float.clear();
        addGlmObject(v);
        _type = Type::Vector4;
        return *this;
    }


    UniformValue& UniformValue::operator=(const glm::mat2& m)
    {
        _float.clear();
        addGlmObject(m);
        _type = Type::Matrix2;
        return *this;
    }

    UniformValue& UniformValue::operator=(const glm::mat3& m)
    {
        _float.clear();
        addGlmObject(m);
        _type = Type::Matrix3;
        return *this;
    }

    UniformValue& UniformValue::operator=(const glm::mat4& m)
    {
        _float.clear();
        addGlmObject(m);
        _type = Type::Matrix4;
        return *this;
    }

    UniformValue& UniformValue::operator=(std::initializer_list<GLfloat> fs)
    {
        _float = fs;
        _type = Type::Float;
        return *this;
    }

    UniformValue& UniformValue::operator=(std::initializer_list<GLint> is)
    {
        _int = is;
        _type = Type::Int;
        return *this;
    }

    UniformValue& UniformValue::operator=(std::initializer_list<glm::mat2> ms)
    {
        _float.clear();
        for(auto& m : ms)
        {
            addGlmObject(m);
        }
        _type = Type::Matrix2;
        return *this;
    }

    UniformValue& UniformValue::operator=(std::initializer_list<glm::mat3> ms)
    {
        _float.clear();
        for(auto& m : ms)
        {
            addGlmObject(m);
        }
        _type = Type::Matrix3;
        return *this;
    }

    UniformValue& UniformValue::operator=(std::initializer_list<glm::mat4> ms)
    {
        _float.clear();
        for(auto& m : ms)
        {
            addGlmObject(m);
        }
        _type = Type::Matrix4;
        return *this;
    }

    UniformValue::Type UniformValue::getType() const
    {
        return _type;
    }

    void UniformValue::set(GLint location) const
    {
        switch(_type)
        {
        case Type::Vector2:
            glUniform2f(location, _float.at(0), _float.at(1));
            break;
        case Type::Vector3:
            glUniform3f(location, _float.at(0), _float.at(1), _float.at(2));
            break;
        case Type::Vector4:
            glUniform4f(location, _float.at(0), _float.at(1),
                _float.at(2), _float.at(3));
            break;
        case Type::Float:
            glUniform1fv(location, (GLsizei)_float.size(), _float.data());
            break;
        case Type::Int:
            glUniform1iv(location, (GLsizei)_int.size(), _int.data());
            break;
        case Type::Matrix2:
            glUniformMatrix2fv(location,
                (GLsizei)_float.size()/getGlmSize<glm::mat2>(),
                false, _float.data());
            break;
        case Type::Matrix3:
            glUniformMatrix3fv(location,
                (GLsizei)_float.size()/getGlmSize<glm::mat3>(),
                false, _float.data());
            break;
        case Type::Matrix4:
            glUniformMatrix4fv(location,
                (GLsizei)_float.size()/getGlmSize<glm::mat4>(),
                false, _float.data());
            break;
        default:
            break;
        }

        checkGlError("setting uniform value");
    }

    bool UniformValue::empty() const
    {
        return _type == Type::Empty;
    }
}

