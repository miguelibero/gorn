#ifndef __gorn__Math__
#define __gorn__Math__

#include <glm/glm.hpp>

namespace gorn
{
    class Math
    {
    public:
		Math() = delete;

		static bool areEqual(const double& a, const double& b);
		static bool areEqual(const float& a, const float& b);

		static bool isZero(const glm::vec2& v);
		static bool isZero(const glm::vec3& v);
		static bool isZero(const glm::vec4& v);
		static bool isZero(const float& v);
		static bool isZero(const double& v);
    };



}

#endif
