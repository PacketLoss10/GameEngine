#pragma once

#include "EngineUtils.h"

using TextureRect = IRect;

struct FrameData
{
	std::string path = "nulltexture.png";
	TextureRect rect = TextureRect(IVector(0, 0), IVector(1, 1));
	FrameData() {}
	FrameData(std::string path, TextureRect rect) :path(path), rect(rect) {}
};

class RenderObject 
{
protected:
	FrameData data;
	RenderObject();
	RenderObject(FrameData data);
public:
	const FrameData& get_data() const;
	void set_path(const std::string& new_path);
	void set_rect(const TextureRect& new_rect);
	void set_position(const IVector& new_position);
	void set_size(const IVector& new_size);
};