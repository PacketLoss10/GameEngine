#pragma once

#include "Vector.h"

class Transform :public SLObject
{
public:
	FVector position = FVector(0.f, 0.f);
	FVector forward = FVector(1.f, 0.f);
	FVector scale = FVector(1.f, 1.f);

	Transform() {}
	Transform(FVector position, FVector forward, FVector scale) :position(position), forward(forward), scale(scale) {}

	TO_JSON(
		json.set("position", position);
	json.set("forward", forward);
	json.set("scale", scale);
		)

		FROM_JSON(
			position = json.get("position");
	forward = json.get("forward");
	scale = json.get("scale");
		)
};