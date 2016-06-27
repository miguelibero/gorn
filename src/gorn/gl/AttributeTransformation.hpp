#ifndef __gorn__AttributeTransformation__
#define __gorn__AttributeTransformation__

#include <glm/glm.hpp>
#include <functional>
class buffer;

namespace gorn
{
	class AttributeDefinition;

	class AttributeTransformation
	{
	public:
		typedef AttributeDefinition Definition;
		typedef std::function<void(const AttributeDefinition& def, buffer& elms, const glm::mat4& transform)> Function;

		AttributeTransformation() = delete;
		static void position(const Definition& def, buffer& elms, const glm::mat4& trans);
		static void normal(const Definition& def, buffer& elms, const glm::mat4& trans);
		static Function create(const std::string& name);
	};
}

#endif

