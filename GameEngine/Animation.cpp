#include "Animation.h"
#include "TickClock.h"

Animation::Animation(SpriteComponent* sprite, IntVector frameSize, int numFrames, float duration, bool looping) :sprite(sprite), frameSize(frameSize), numFrames(numFrames), frameLength(duration / static_cast<float>(numFrames)), looping(looping) {}

void Animation::update()
{
	elapsedTime += DELTA_TIME;
	if (elapsedTime < frameLength || paused || (!looping && is_finished()))
		return;

	elapsedTime = 0.f;

	currentFrame++;
	currentFrame %= numFrames;

	TextureRect nextFrame = TextureRect(
		IntVector(
			(currentFrame % sprite->get_rect().get_size().x) * frameSize.x,
			(currentFrame / sprite->get_rect().get_size().x) * frameSize.y),
		frameSize
	);

	sprite->set_rect(nextFrame);
}

void Animation::pause()
{
	paused = true;
}

void Animation::play()
{
	paused = false;
}

bool Animation::is_paused() const
{
	return paused;
}

bool Animation::is_finished() const
{
	return currentFrame == numFrames - 1;
}

bool Animation::is_looping() const
{
	return looping;
}

void Animation::set_looping(bool looping)
{
	this->looping = looping;
}

float Animation::get_duration() const
{
	return frameLength * static_cast<float>(numFrames);
}

void Animation::set_duration(float duration)
{
	frameLength = duration / static_cast<float>(numFrames);
}