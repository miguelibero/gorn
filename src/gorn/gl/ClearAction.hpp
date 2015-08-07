#ifndef __gorn__ClearAction__
#define __gorn__ClearAction__

#include <gorn/gl/GlEnums.hpp>
#include <glm/glm.hpp>
#include <vector>

namespace gorn
{
	class ClearAction
	{
    public:
        typedef ClearType Type;
        typedef std::vector<Type> Types;
    private:
        glm::vec4 _color;
        Types _types;
	public:
		ClearAction();

        ClearAction& withColor(const glm::vec4& color);
        ClearAction& withType(Type type);

        bool empty() const;
		
        void apply();

    };
}

#endif
