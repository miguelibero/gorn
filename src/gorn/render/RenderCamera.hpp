#ifndef __gorn__RenderCamera__
#define __gorn__RenderCamera__

#include <gorn/gl/UniformValue.hpp>
#include <gorn/gl/BlendMode.hpp>
#include <gorn/base/Frustum.hpp>
#include <glm/glm.hpp>
#include <map>

namespace gorn
{
	class RenderCamera
	{
	public:
		typedef std::vector<int> Layers;
	private:
		glm::mat4 _view;
		glm::mat4 _proj;
		glm::vec3 _position;
		Frustum _frustum;
		bool _dirty;
		BlendMode _blendMode;
		UniformValueMap _uniformValues;
		Layers _layers;
	public:
		RenderCamera();
		RenderCamera& withView(const glm::mat4& view);
		RenderCamera& withProjection(const glm::mat4& proj);
		RenderCamera& withBlendMode(const BlendMode& blend);
		RenderCamera& withUniformValue(const std::string& name, const UniformValue& value);
		RenderCamera& withUniformValues(const UniformValueMap& values);
		RenderCamera& withLayer(int layer);
		RenderCamera& withLayers(const Layers& layers);

		void update();
		const UniformValueMap& getUniformValues() const;
		const Frustum& getFrustum() const;
		const BlendMode& getBlendMode() const;
		const Layers& getLayers() const;

		bool matchesLayers(const Layers& layers) const;
		glm::vec3 getScreenToWorldPoint(const glm::vec2& p) const;
		glm::vec2 getWorldToScreenPoint(const glm::vec3& p) const;
	};

}

#endif
