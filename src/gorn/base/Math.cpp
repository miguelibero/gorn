
#include <gorn/base/Math.hpp>
#include <limits>
#include <algorithm>
#include <random>

namespace gorn
{
	bool Math::areEqual(const double& a, const double& b)
	{
		return std::abs(a - b) <= std::numeric_limits<double>::epsilon() * std::max(std::abs(a), std::abs(b));
	}

	bool Math::areEqual(const float& a, const float& b)
	{
		return std::abs(a - b) <= std::numeric_limits<float>::epsilon() * std::max(std::abs(a), std::abs(b));
	}

	bool Math::isZero(const glm::vec2& v)
	{
		return isZero(v.x) && isZero(v.y);
	}

	bool Math::isZero(const glm::vec3& v)
	{
		return isZero(v.x) && isZero(v.y) && isZero(v.z);
	}

	bool Math::isZero(const glm::vec4& v)
	{
		return isZero(v.r) && isZero(v.g) && isZero(v.b) && isZero(v.a);
	}

	bool Math::isZero(const float& v)
	{
		return areEqual(v, 0.0f);
	}

	bool Math::isZero(const double& v)
	{
		return areEqual(v, 0.0);
	}

	static std::random_device randomDevice;

	double Math::random(double from, double to)
	{
		std::mt19937 randomEngine(randomDevice());
		std::uniform_real_distribution<double> dis(from, to);
		return dis(randomEngine);
	}

	float Math::random(float from, float to)
	{
		std::mt19937 randomEngine(randomDevice());
		std::uniform_real_distribution<float> dis(from, to);
		return dis(randomEngine);
	}

	int Math::random(int from, int to)
	{
		std::mt19937 randomEngine(randomDevice());
		std::uniform_int_distribution<int> dis(from, to);
		return dis(randomEngine);
	}
}

