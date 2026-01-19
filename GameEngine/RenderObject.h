#pragma once

#include "Transformable.h"

class ZSortable
{
private:
	int zOrder = 0;
public:
	ZSortable() = default;
	ZSortable(int zOrder) :zOrder(zOrder) {}
	int get_zOrder() const
	{
		return zOrder;
	}
	void set_zOrder(int zOrder)
	{
		this->zOrder = zOrder;
	}
};

class RenderObject: public Transformable 
{
private:
public:
	RenderObject() = default;
	RenderObject(Transform transform);
	virtual ~RenderObject() = default;
};