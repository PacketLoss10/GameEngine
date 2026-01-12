#include "Animation.h"

Animation::Animation(Sprite sprite, AnimLayout layout, IVector frameSize, int numFrames, float fps, bool oneShot, bool autoStart) :sprite(sprite), layout(layout), frameSize(frameSize), numFrames(numFrames), dt(1.f / std::max(fps, 0.01f)), oneShot(oneShot), paused(!autoStart) {}

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