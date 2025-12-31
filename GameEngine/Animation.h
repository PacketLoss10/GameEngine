//#pragma once
//
//#include "EngineUtils.h"
//#include "RenderObject.h"
//#include "TickClock.h"
//
//class Animation :public RenderObject 
//{
//private:
//	IVector layout = IVector(1, 1);
//	IVector start = IVector(0, 0);
//	int numFrames = 1;
//	int currentFrame = 0;
//	float dt = 0.f;
//	bool oneshot = false;
//	sf::Clock clock;
//public:
//	Animation();
//	Animation(std::string texturePath, IVector layout, IVector start, IVector frameSize, int numFrames, float fps, bool oneshot);
//	void update();
//	void set_currentFrame(int new_currentFrame);
//	void set_duration(float new_duration);
//	bool is_finished() const;
//};
#pragma once

#include "Sprite.h"
#include "EngineUtils.h"

class Animation :public Sprite
{
private:
	IRect layout;
	int numFrames;
	int currentFrame;
	float dt;
	bool oneshot;
	sf::Clock clock;
public:
	Animation();
	Animation(std::string texture, IVector frameSize, std::string normalMap, IRect layout, int numFrames, float fps, float oneshot);
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