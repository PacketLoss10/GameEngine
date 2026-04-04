#pragma once

#include "SpriteComponent.h"

class Animation
{
private:
	SpriteComponent* sprite = nullptr;
	IntVector frameSize = IntVector(1, 1);
	int numFrames = 1;
	int currentFrame = 0;
	float elapsedTime = 0.f;
	float frameLength = 0.f;
	bool looping = false;
	bool paused = false;
public:
	Animation() = default;
	Animation(SpriteComponent* sprite, IntVector frameSize, int numFrames, float duration, bool looping);

	void update();
	void pause();
	void play();

	bool is_paused() const;
	bool is_finished() const;

	bool is_looping() const;
	void set_looping(bool looping);

	float get_duration() const;
	void set_duration(float duration);
};