#ifndef __gorn__
#define __gorn__

#include <gorn/base/Application.hpp>
#include <gorn/render/RenderContext.hpp>
#include <gorn/render/MaterialDefinition.hpp>
#include <gorn/render/VertexBuffer.hpp>
#include <gorn/render/VertexArray.hpp>
#include <gorn/render/VertexDefinition.hpp>
#include <gorn/render/AttributeBinding.hpp>
#include <gorn/render/UniformValue.hpp>
#include <gorn/asset/Image.hpp>
#include <gorn/asset/TextureAtlas.hpp>

#ifdef GORN_PLATFORM_LINUX
#include <gorn/platform/linux/LocalFileLoader.hpp>
#include <gorn/platform/linux/PngImageLoader.hpp>
#elif GORN_PLATFORM_ANDROID
#include <gorn/platform/android/BundleFileLoader.hpp>
#include <gorn/platform/android/GraphicsImageLoader.hpp>
#endif

#endif
