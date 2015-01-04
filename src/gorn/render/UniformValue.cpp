#include <gorn/render/UniformValue.hpp>

namespace gorn
{
	UniformValue::UniformValue():
    _type(Type::Empty)
    {
    }

	UniformValue::UniformValue(GLfloat f):
    _float{f}, _type(Type::Float)
    {
    }

	UniformValue::UniformValue(GLint i):
    _int{i}, _type(Type::Int)
    {
    }

	UniformValue::UniformValue(GLuint u):
    _uint{u}, _type(Type::UnsignedInt)
    {
    }

	UniformValue::UniformValue(const glm::mat2& m):
    _mat2{m}, _type(Type::Matrix2)
    {
    }

	UniformValue::UniformValue(const glm::mat3& m):
    _mat3{m}, _type(Type::Matrix3)
    {
    }

	UniformValue::UniformValue(const glm::mat4& m):
    _mat4{m}, _type(Type::Matrix4)
    {
    }

    UniformValue::UniformValue(std::initializer_list<GLfloat> fs):
    _float(fs), _type(Type::Float)
    {
    }

	UniformValue::UniformValue(std::initializer_list<GLint> is):
    _int(is), _type(Type::Int)
    {
    }

	UniformValue::UniformValue(std::initializer_list<GLuint> us):
    _uint(us), _type(Type::UnsignedInt)
    {
    }

	UniformValue::UniformValue(std::initializer_list<glm::mat2> ms):
    _mat2(ms), _type(Type::Matrix2)
    {
    }

	UniformValue::UniformValue(std::initializer_list<glm::mat3> ms):
    _mat3(ms), _type(Type::Matrix3)
    {
    }

	UniformValue::UniformValue(std::initializer_list<glm::mat4> ms):
    _mat4(ms), _type(Type::Matrix4)
    {
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

	UniformValue& UniformValue::operator=(GLuint u)
    {
        _uint = {u};
        _type = Type::UnsignedInt;
        return *this;
    }

	UniformValue& UniformValue::operator=(const glm::mat2& m)
    {
        _mat2 = {m};
        _type = Type::Matrix2;
        return *this;
    }

	UniformValue& UniformValue::operator=(const glm::mat3& m)
    {
        _mat3 = {m};
        _type = Type::Matrix3;
        return *this;
    }

	UniformValue& UniformValue::operator=(const glm::mat4& m)
    {
        _mat4 = {m};
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

	UniformValue& UniformValue::operator=(std::initializer_list<GLuint> us)
    {
        _uint = us;
        _type = Type::UnsignedInt;
        return *this;
    }

	UniformValue& UniformValue::operator=(std::initializer_list<glm::mat2> ms)
    {
        _mat2 = ms;
        _type = Type::Matrix2;
        return *this;
    }

	UniformValue& UniformValue::operator=(std::initializer_list<glm::mat3> ms)
    {
        _mat3 = ms;
        _type = Type::Matrix3;
        return *this;
    }

	UniformValue& UniformValue::operator=(std::initializer_list<glm::mat4> ms)
    {
        _mat4 = ms;
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
        case Type::Float:
            glUniform1fv(location, _float.size(), _float.data());
            break;
        case Type::Int:
            glUniform1iv(location, _int.size(), _int.data());
            break;
        case Type::UnsignedInt:
#ifdef GORN_PLATFORM_ANDROID
#else
            glUniform1uiv(location, _uint.size(), _uint.data());
#endif
            break;
        case Type::Matrix2:
            glUniformMatrix2fv(location, _mat2.size(), false,
                reinterpret_cast<const GLfloat*>(_mat2.data()));
            break;
        case Type::Matrix3:
            glUniformMatrix3fv(location, _mat3.size(), false,
                reinterpret_cast<const GLfloat*>(_mat3.data()));
            break;
        case Type::Matrix4:
            glUniformMatrix4fv(location, _mat4.size(), false,
                reinterpret_cast<const GLfloat*>(_mat4.data()));
            break;
        default:
            break;
        }
    }

}

