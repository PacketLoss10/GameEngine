#pragma once

#include "Component.h"
#include "Sprite.h"
#include "Vector.h"

class AnimLayout
{
public:
	IVector start = IVector(0, 0);
	IVector size = IVector(1, 1);
	AnimLayout() = default;
	AnimLayout(IVector start, IVector size) :start(IVector(std::max(0, start.x), std::max(0, start.y))), size(IVector(std::max(1, size.x), std::max(1, size.y))) {}
	operator sf::IntRect() const
	{
		return sf::IntRect(start, size);
	}
};

class Animation :public Component
{
private:
	Sprite sprite = Sprite();
	AnimLayout layout = AnimLayout();
	IVector frameSize = IVector();
	int numFrames = 1;
	int currentFrame = 0;
	float dt = 0.f;
	bool oneShot = false;
	sf::Clock clock;
	bool paused = false;
public:
	Animation() = default;

	void init(Entity* owner, bool enabled, Sprite sprite, AnimLayout layout, IVector frameSize, int numFrames, float fps, bool oneShot, bool autoStart);

	void update();
	void pause();
	void play();
	bool is_paused() const;
	bool is_finished() const;
};