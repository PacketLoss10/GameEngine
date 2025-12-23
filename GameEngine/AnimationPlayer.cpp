#include "AnimationPlayer.h"

AnimationPlayer::AnimationPlayer(Animation defaultAnimation) :defaultAnimation(defaultAnimation) {}

AnimationPlayer::AnimationPlayer(Animation defaultAnimation, std::vector<std::pair<std::string, Animation>> animations) :defaultAnimation(defaultAnimation)
{
	for (const auto& [name, animation] : animations)
		animationMap[name] = animation;
}

void AnimationPlayer::update()
{
	if (current)
		current->update();
	else defaultAnimation.update();
}

void AnimationPlayer::bind(std::string name, Animation animation)
{
	animationMap[name] = animation;
}

const Animation& AnimationPlayer::get_current() const 
{
	return current ? *current : defaultAnimation; 
}

bool AnimationPlayer::is_playing(const std::string& name) const 
{
	if (auto it = animationMap.find(name); it != animationMap.end())
		return &animationMap.at(name) == current;
	else return false;
}

void AnimationPlayer::play_animation(const std::string& name, bool restart)
{
	if (auto it = animationMap.find(name); it != animationMap.end()) 
	{
		current = &it->second;
		if (restart)
			current->set_currentFrame(0);
	}
	else 
	{
		current = &defaultAnimation;
		if (restart)
			current->set_currentFrame(0);
	}
}

void AnimationPlayer::set_duration(const std::string& name, float duration)
{
	if (auto it = animationMap.find(name); it != animationMap.end())
		it->second.set_duration(duration);
	else defaultAnimation.set_duration(duration);
}

const Animation& AnimationPlayer::get_animation(const std::string& name) const
{
	if (auto it = animationMap.find(name); it != animationMap.end())
		return it->second;
	else return defaultAnimation;
}

const Animation* AnimationPlayer::find(const std::string& name) const
{
	if (auto it = animationMap.find(name); it != animationMap.end())
		return &it->second;
	else return nullptr;
}