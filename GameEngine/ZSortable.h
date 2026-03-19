#pragma once

#include "unordered_set"
#include "algorithm"

class ZSortable
{
private:
	static std::vector<int> others;
	int zOrder = 0;
public:
	ZSortable(int zOrder);

	int get_zOrder() const;
	void set_zOrder(int zOrder);

	void to_front();
	void to_back();
};