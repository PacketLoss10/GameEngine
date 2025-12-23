#pragma once

#include "EngineUtils.h"
#include "TextureLoader.h"
#include "GameWindow.h"
#include "RenderObject.h"

#define RENDERER Renderer::instance()

class Renderer 
{
private:
	Renderer() = default;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
public:
	static Renderer& instance();
	void start_render() const;
	void render(const FrameData& data, const Transform& transform);
	void end_render() const;
};