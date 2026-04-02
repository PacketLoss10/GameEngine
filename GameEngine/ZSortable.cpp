#include "ZSortable.h"
#include "iostream"

std::vector<ZSortable*> ZSortable::others;

ZSortable::ZSortable(int zOrder) :zOrder(zOrder)
{
	others.push_back(this);
	std::sort(others.begin(), others.end(), [](const ZSortable* lhs, const ZSortable* rhs) { return lhs->get_zOrder() < rhs->get_zOrder(); });
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
	if (others.size() <= 1)
		return;

	ZSortable* frontmost = others.back();
	int greatestZ = frontmost->get_zOrder();

	if (this != frontmost)
	{
		zOrder = greatestZ + 1;
		std::sort(others.begin(), others.end(), [](const ZSortable* lhs, const ZSortable* rhs) { return lhs->get_zOrder() < rhs->get_zOrder(); });
	}
}

void ZSortable::to_back()
{
	if (others.size() <= 1)
		return;

	ZSortable* backmost = others.front();
	int leastZ = backmost->get_zOrder();

	if (this != backmost)
	{
		zOrder = leastZ - 1;
		std::sort(others.begin(), others.end(), [](const ZSortable* lhs, const ZSortable* rhs) { return lhs->get_zOrder() < rhs->get_zOrder(); });
	}
}