#pragma once

#include "EngineUtils.h"
#include "RenderObject.h"
#include "TickClock.h"

class Animation :public RenderObject 
{
private:
	IVector layout = IVector(1, 1);
	IVector start = IVector(0, 0);
	int numFrames = 1;
	int currentFrame = 0;
	float dt = 0.f;
	bool oneshot = false;
	sf::Clock clock;
public:
	Animation();
	Animation(std::string texturePath, IVector layout, IVector start, IVector frameSize, int numFrames, float fps, bool oneshot);
	void update();
	void set_currentFrame(int new_currentFrame);
	void set_duration(float new_duration);
	bool is_finished() const;
};