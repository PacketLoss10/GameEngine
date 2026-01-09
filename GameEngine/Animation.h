#pragma once

#include "Sprite.h"
#include "core.h"

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
	TO_JSON(
		json.set("diffuse", texture);
	json.set("normal", normalMap);
	json.set("transform", transform);
	json.set("layout", layout);
	json.set("frameSize", frameSize);
	json.set("numFrames", numFrames);
	json.set("currentFrame", currentFrame);
	json.set("dt", dt);
	json.set("oneshot", oneshot);
		)
		FROM_JSON(
			texture = json.get("diffuse");
	normalMap = json.get("normal");
	transform = json.get("transform");
	layout = json.get("layout");
	frameSize = json.get("frameSize");
	numFrames = json.get("numFrames");
	currentFrame = json.get("currentFrame");
	dt = json.get("dt");
	oneshot = json.get("oneshot");
		)
};