#include "Animation.h"

void Animation::init(Entity* owner, bool enabled, Sprite sprite, AnimLayout layout, IVector frameSize, int numFrames, float fps, bool oneShot, bool autoStart)
{
	this->owner = owner;
	this->enabled = enabled;
	this->sprite = sprite;
	this->layout = layout;
	this->frameSize = frameSize;
	this->numFrames = std::max(1, numFrames);
	this->dt = 1.f / fps;
	this->oneShot = oneShot;
	this->paused = !autoStart;
}

void Animation::update()
{
	if (clock.getElapsedTime().asSeconds() < dt || paused || (oneShot && is_finished()))
		return;

	clock.restart();

	currentFrame = (currentFrame + 1) % numFrames;

	sprite.set_rect(TextureRect(
		layout.start.component_wise_mult(frameSize) +
		IVector(
			(currentFrame % layout.size.x) * frameSize.x,
			(currentFrame / layout.size.x) * frameSize.y),
		frameSize));
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