#ifndef __gorn__platform__
#define __gorn__platform__

#ifdef GORN_PLATFORM_LINUX
#include <gorn/platform/linux/LocalFileLoader.hpp>
#include <gorn/platform/linux/PngImageLoader.hpp>
#elif GORN_PLATFORM_ANDROID
#include <gorn/platform/android/BundleFileLoader.hpp>
#include <gorn/platform/android/GraphicsImageLoader.hpp>
#endif

#endif