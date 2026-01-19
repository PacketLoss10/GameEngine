#pragma once

#include "Transform.h"

class NavBlock
{
private:
	FVector position = FVector();
	FVector size = FVector();
public:
	NavBlock() = default;
	NavBlock(FVector position, FVector size);

	const FVector& get_position() const;
	const FVector& get_size() const;
};