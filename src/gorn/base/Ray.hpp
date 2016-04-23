#ifndef __gorn__Ray__
#define __gorn__Ray__

#include <glm/glm.hpp>

namespace gorn
{
	class Rect;

    class Ray
    {
	private:
		bool clipLine(int d, const Rect& rect, float& f_low, float& f_high) const;
    public:
		glm::vec3 origin;
		glm::vec3 direction;

		Ray(const glm::vec3& origin, const glm::vec3& dir);

		bool hits(const Rect& rect) const;
		bool hits(const Rect& rect, glm::vec3& pos) const;
		Ray transform(const glm::mat4& m) const;
    };
}

#endif
