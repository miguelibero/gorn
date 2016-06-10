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

		static double random(double from, double to);
		static float random(float from, float to);
		static int random(int from, int to);


		template<typename T>
		static T clamp(T val, T min, T max)
		{
			if(val < min)
			{
				return min;
			}
			else if(val > max)
			{
				return max;
			}
			return x;
		}

		template<typename T>
		static T lerp(T v0, T v1, T t)
		{
			return (1 - t)*v0 + t*v1;
		}
    };



}

#endif
