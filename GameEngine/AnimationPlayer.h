#pragma once

#include "core.h"
#include "Animation.h"

class AnimationPlayer 
{
private:
	std::unordered_map<std::string, Animation> animationMap;
	Animation defaultAnimation;
	Animation* current = nullptr;
public:
	AnimationPlayer(Animation defaultAnimation);
	AnimationPlayer(Animation defaultAnimation, std::vector<std::pair<std::string, Animation>> animations);
	void update();
	void bind(std::string name, Animation animation);
	const Animation& get_current() const;
	bool is_playing(const std::string& name) const;
	void play_animation(const std::string& name, bool restart = false);
	void set_duration(const std::string& name, float duration);
	const Animation& get_animation(const std::string& name) const;
	const Animation* find(const std::string& name) const;
};