#include "RenderObject.h"

RenderObject::RenderObject() :data(FrameData()) {}

RenderObject::RenderObject(FrameData data) :data(data) {}

const FrameData& RenderObject::get_data() const 
{ 
	return data; 
}

void RenderObject::set_path(const std::string& new_path) 
{
	data.path; 
}

void RenderObject::set_rect(const TextureRect& new_rect) 
{ 
	data.rect = new_rect; 
}

void RenderObject::set_position(const IVector& new_position) 
{ 
	data.rect.position = new_position;
}

void RenderObject::set_size(const IVector& new_size) 
{ 
	data.rect.size = new_size;
}