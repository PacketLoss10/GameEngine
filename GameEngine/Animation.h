#pragma once

#include "Component.h"
#include "Sprite.h"
#include "Transform.h"

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

class Animation :public Component, public Transformable
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
	Animation(Entity* owner, bool enabled, Sprite sprite, AnimLayout layout, IVector frameSize, int numFrames, float fps, bool oneShot, bool autoStart);
	Animation(Entity* owner, bool enabled, int zOrder, Transform transform, Texture texture, AnimLayout layout, IVector frameSize, int numFrames, float fps, bool oneShot, bool autoStart);
	Animation(Entity* owner, bool enabled, int zOrder, Transform transform, Texture texture, NormalMap normal, AnimLayout layout, IVector frameSize, int numFrames, float fps, bool oneShot, bool autoStart);

	void init() override;

	void update();
	void pause();
	void play();
	bool is_paused() const;
	bool is_finished() const;
};