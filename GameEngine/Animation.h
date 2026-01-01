#pragma once

#include "Sprite.h"
#include "EngineUtils.h"

class Animation :public Sprite
{
private:
	IRect layout;
	IVector frameSize;
	int numFrames;
	int currentFrame;
	float dt;
	bool oneshot;
	sf::Clock clock;
public:
	Animation();
	Animation(std::string sheet, IVector frameSize, IRect layout, int numFrames, float fps, float oneshot);
	void update();
	int get_numFrames() const;
	int get_currentFrame() const;
	void set_currentFrame(int new_currentFrame);
	bool is_oneshot() const;
	void set_oneshot(bool new_oneshot);
	float get_duration() const;
	void set_duration(float new_duration);
	bool is_finished() const;
};