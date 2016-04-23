#include <gorn/base/Ray.hpp>
#include <gorn/base/Rect.hpp>
#include <gorn/base/Math.hpp>
#include <algorithm>

namespace gorn
{
	Ray::Ray(const glm::vec3& origin, const glm::vec3& dir):
	origin(origin), direction(dir)
	{
	}

	bool Ray::hits(const Rect& rect) const
	{
		return false;
	}

	bool Ray::hits(const Rect& rect, glm::vec3& pos) const
	{
		// taken from Math for game developers
		// https://github.com/BSVino/MathForGameDevelopers/blob/7523d2edf2453c2e700ad8cc36c8a3882689ca8c/math/collision.cpp
		auto high = std::numeric_limits<float>::infinity();
		auto low = -1.0f*high;

		if(!clipLine(0, rect, low, high))
		{
			return false;
		}
		if(!clipLine(1, rect, low, high))
		{
			return false;
		}
		if(!clipLine(2, rect, low, high))
		{
			return false;
		}
		pos = origin + direction * low;
		return true;
	}

	bool Ray::clipLine(int d, const Rect& rect, float& low, float& high) const
	{
		auto dir = direction[d];
		auto ori = origin[d];
		auto min = rect.min()[d];
		auto max = rect.max()[d];
		auto dimLow = (min - ori) / dir;
		auto dimHigh = (max - ori) / dir;
		if (dimHigh < dimLow)
		{
			std::swap(dimHigh, dimLow);
		}
		if (dimHigh < low)
		{
			return false;
		}
		if (dimLow > high)
		{
			return false;
		}
		low = std::max(dimLow, low);
		high = std::min(dimHigh, high);
		return low <= high;
	}

	Ray Ray::transform(const glm::mat4& m) const
	{
		auto a = glm::vec3(m * glm::vec4(origin, 1.0f));
		auto b = glm::vec3(m * glm::vec4(origin + direction, 1.0f));
		return Ray(a, b - a);
	}
}
