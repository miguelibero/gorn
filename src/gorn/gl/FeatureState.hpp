#ifndef __gorn__FeatureState__
#define __gorn__FeatureState__

#include <gorn/gl/GlEnums.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace gorn
{
	class FeatureState
	{
    public:
        typedef FeatureType Type;
        typedef std::vector<Type> Types;
    private:
        Types _enables;
        Types _disables;
	public:
		FeatureState();

        FeatureState& withEnable(FeatureType type);
        FeatureState& withDisable(FeatureType type);

        bool operator==(const FeatureState& other) const;
        bool operator!=(const FeatureState& other) const;
		
        void apply();

        static FeatureState current();
    };
}

#endif
