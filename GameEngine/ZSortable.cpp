#include "ZSortable.h"

ZSortable::ZSortable(int zOrder) :zOrder(zOrder)
{
	others.push_back(zOrder);
	std::sort(others.begin(), others.end(), [](const int lhs, const int rhs) { return lhs < rhs; });
}

int ZSortable::get_zOrder() const
{
	return zOrder;
}

void ZSortable::set_zOrder(int zOrder)
{
	this->zOrder = zOrder;
}

void ZSortable::to_front()
{
	if (others.empty())
		return;

	zOrder = others.back();
}

void ZSortable::to_back()
{
	if (others.empty())
		return;

	zOrder = others.front();
}