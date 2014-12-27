//
//  Application.cpp
//  OpenglGame
//
//  Created by mibero on 14/10/14.
//  Copyright (c) 2014 Miguel Ibero. All rights reserved.
//

#include <gorn/base/Application.hpp>
#include <gorn/base/Log.hpp>
#include <gorn/platform/PlatformBridge.hpp>
#include <gorn/render/Renderer.hpp>
#include <gorn/render/ProgramDefinition.hpp>
#include <gorn/render/MaterialDefinition.hpp>

namespace gorn
{
	PlatformBridge _bridge;
	Renderer _renderer;

	Application::Application()
	{
	}

	void Application::load()
	{
		_renderer.setPlatformBridge(_bridge);
	    _renderer.defineProgram("sprite",
	        ProgramDefinition("shaders/sprite.vsh", "shaders/sprite.fsh")
	        .withUniforms({"projView"})
	        .withAttributes({"position", "texCoord", "color"}));
	    _renderer.defineMaterial("sprite",
	        MaterialDefinition("sprite")
	        .withTextures({"textures/checkers.jpg"}));
	}

	void Application::unload()
	{   
	}

	void Application::update(double dt)
	{
		_renderer.draw();
	}

}