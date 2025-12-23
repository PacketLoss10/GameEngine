#include "Animation.h"

Animation::Animation() :RenderObject() {}

Animation::Animation(std::string texturePath, IVector layout,IVector start, IVector frameSize, int numFrames, float fps, bool oneshot) :RenderObject(FrameData(texturePath, IRect(start, frameSize))), layout(IVector(std::max(1, layout.x), std::max(1, layout.y))), start(IVector(std::max(0, start.x), std::max(0, start.y))), numFrames(std::max(1, numFrames)), dt(1.f / fps), oneshot(oneshot) {}

void Animation::update() 
{
	if (clock.getElapsedTime().asSeconds() < dt)
		return;

	clock.restart();

	if (oneshot && is_finished())
		return;

	currentFrame = (currentFrame + 1) % numFrames;

	data.rect = IRect(
		start.component_wise_mult(data.rect.size) +
		IVector(
			(currentFrame % layout.x) * data.rect.size.x,
			(currentFrame / layout.x) * data.rect.size.y),
		data.rect.size);
}

void Animation::set_currentFrame(int new_currentFrame) 
{
	currentFrame = new_currentFrame;
}

void Animation::set_duration(float new_duration) 
{
	dt = 1.f / (static_cast<float>(numFrames) / new_duration);
}

bool Animation::is_finished() const 
{ 
	return currentFrame == numFrames - 1;
}