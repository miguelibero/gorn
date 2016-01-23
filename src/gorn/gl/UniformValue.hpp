#ifndef __gorn__UniformValue__
#define __gorn__UniformValue__

#include <gorn/gl/Base.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <initializer_list>

namespace gorn
{
    enum class UniformValueType
    {
        Empty,
        Float,
        Int,
        Vector2,
        Vector3,
        Vector4,
        Matrix2,
        Matrix3,
        Matrix4
    };

    class UniformValue
    {
    private:
        typedef UniformValueType Type;

        std::vector<GLfloat> _float;
        std::vector<GLint> _int;

        Type _type;

        template<typename T>
        static size_t getGlmSize();

        template<typename T>
        void addGlmObject(const T& obj)
        {
            auto ptr = glm::value_ptr(obj);
            _float.insert(_float.end(), ptr, ptr + getGlmSize<T>());
        }

    public:
        UniformValue();
        UniformValue(GLfloat f);
        UniformValue(GLint i);
        UniformValue(const glm::vec2& v);
        UniformValue(const glm::vec3& v);
        UniformValue(const glm::vec4& v);
        UniformValue(const glm::mat2& m);
        UniformValue(const glm::mat3& m);
        UniformValue(const glm::mat4& m);

        UniformValue(std::initializer_list<GLfloat> fs);
        UniformValue(std::initializer_list<GLint> is);
        UniformValue(std::initializer_list<glm::mat2> ms);
        UniformValue(std::initializer_list<glm::mat3> ms);
        UniformValue(std::initializer_list<glm::mat4> ms);

        UniformValue& operator=(GLfloat f);
        UniformValue& operator=(GLint i);
        UniformValue& operator=(const glm::vec2& v);
        UniformValue& operator=(const glm::vec3& v);
        UniformValue& operator=(const glm::vec4& v);
        UniformValue& operator=(const glm::mat2& m);
        UniformValue& operator=(const glm::mat3& m);
        UniformValue& operator=(const glm::mat4& m);

        UniformValue& operator=(std::initializer_list<GLfloat> fs);
        UniformValue& operator=(std::initializer_list<GLint> is);
        UniformValue& operator=(std::initializer_list<glm::mat2> ms);
        UniformValue& operator=(std::initializer_list<glm::mat3> ms);
        UniformValue& operator=(std::initializer_list<glm::mat4> ms);

        Type getType() const;

        void set(GLint location) const;
        bool empty() const;
    };

}

#endif
