
#include <gorn/render/RenderCamera.hpp>
#include <gorn/base/Ray.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>

namespace gorn
{
	RenderCamera::RenderCamera():
	_dirty(true)
	{
	}

	RenderCamera& RenderCamera::withView(const glm::mat4& view)
	{
		if(_view != view)
		{
			_view = view;
			_dirty = true;
		}
		return *this;
	}
	RenderCamera& RenderCamera::withProjection(const glm::mat4& proj)
	{
		if(_proj != proj)
		{
			_proj = proj;
			_dirty = true;
		}
		return *this;
	}

	RenderCamera& RenderCamera::withUniformValue(const UniformKind& kind, const UniformValue& value)
	{
		_uniformValues[kind] = value;
		return *this;
	}

	RenderCamera& RenderCamera::withUniformValues(const UniformValueMap& values)
	{
		for(auto& p : values)
		{
			_uniformValues[p.first] = p.second;
		}
		return *this;
	}

	RenderCamera& RenderCamera::withLayer(int layer)
	{
		_layers.push_back(layer);
		return *this;
	}

	RenderCamera& RenderCamera::withLayers(const Layers& layers)
	{
		_layers.insert(_layers.end(), layers.begin(), layers.end());
		return *this;
	}

	void RenderCamera::update()
	{
		if(!_dirty)
		{
			return;
		}
		_frustum = Frustum(_proj*_view);
		_position = glm::vec3(glm::inverse(_view)[3]);
		_uniformValues[UniformType::ViewTransform] = _view;
		_uniformValues[UniformType::ProjectionTransform] = _proj;
		_uniformValues[UniformType::CameraPosition] = _position;
		_uniformValues[UniformType::CameraTransform] = _frustum.getMatrix();
		_dirty = false;
	}

	const Frustum& RenderCamera::getFrustum() const
	{
		return _frustum;
	}

	const UniformValueMap& RenderCamera::getUniformValues() const
	{
		return _uniformValues;
	}

	const RenderCamera::Layers& RenderCamera::getLayers() const
	{
		return _layers;
	}

	bool RenderCamera::matchesLayers(const Layers& layers) const
	{
		if(_layers.empty() || layers.empty())
		{
			return true;
		}
		for(auto& l1 : _layers)
		{
			if(std::find(layers.begin(), layers.end(), l1) != layers.end())
			{
				return true;
			}
		}
		return false;
	}

	Ray RenderCamera::getScreenPointRay(const glm::vec2& p) const
	{
		return _frustum.getPointRay(p);
	}

	glm::vec2 RenderCamera::getRayScreenPoint(const Ray& r) const
	{
		return _frustum.getRayPoint(r);
	}
}
