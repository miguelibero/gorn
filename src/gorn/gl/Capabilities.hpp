#ifndef __gorn__Capabilities__
#define __gorn__Capabilities__

#include <gorn/gl/Enums.hpp>
#include <glm/glm.hpp>
#include <map>
#include <vector>

namespace gorn
{
    class Capabilities
    {
    public:
        typedef std::map<CapabilityType,bool> CapabilityChanges;
        typedef std::map<MaskType,bool> MaskChanges;
    private:
		CapabilityChanges _capabilities;
        MaskChanges _masks;
		float _lineWidth;
    public:
		Capabilities();

		Capabilities& with(CapabilityType type, bool enabled = true);
		Capabilities& with(MaskType type, bool enabled = true);

		Capabilities& withLineWidth(float w);

        bool operator==(const Capabilities& other) const;
        bool operator!=(const Capabilities& other) const;
        
        void apply() const;
    };

}

#endif
