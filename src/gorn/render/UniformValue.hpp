#ifndef __gorn__UniformValue__
#define __gorn__UniformValue__

#include <gorn/render/Gl.hpp>
#include <glm/glm.hpp>
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
        std::vector<glm::mat2> _mat2;
        std::vector<glm::mat3> _mat3;
        std::vector<glm::mat4> _mat4;

        Type _type;

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
	};

}

#endif
