#include "Animation.h"

Animation::Animation() :Sprite(), layout(IVector(0, 0), IVector(1, 1)), numFrames(1), currentFrame(0), dt(0.f), oneshot(false) {}

Animation::Animation(std::string sheet, IVector frameSize, IRect layout, int numFrames, float fps, float oneshot)
	:Sprite(sheet,IRect(IVector(std::max(0,layout.position.x),std::max(0,layout.position.y)),IVector(std::max(1,frameSize.x),std::max(1,frameSize.x)))),
	layout(IRect(IVector(std::max(0, layout.position.x), std::max(0, layout.position.y)), IVector(std::max(1, layout.size.x), std::max(1, layout.size.y)))),
	frameSize(IVector(std::max(0,frameSize.x),std::max(0,frameSize.y))),
	numFrames(std::max(1, numFrames)),
	currentFrame(0),
	dt(1.f / fps),
	oneshot(oneshot)
{
}

void Animation::update()
{
	if (clock.getElapsedTime().asSeconds() < dt)
		return;

	clock.restart();

	if (oneshot && is_finished())
		return;

	currentFrame = (currentFrame + 1) % numFrames;

	rect = IRect(
		layout.position.component_wise_mult(frameSize) +
		IVector(
			(currentFrame % layout.size.x) * frameSize.x,
			(currentFrame / layout.size.x) * frameSize.y),
		frameSize);

	std::cout << (std::string)rect.position << std::endl;
}

int Animation::get_numFrames() const
{
	return numFrames;
}

int Animation::get_currentFrame() const
{
	return currentFrame;
}

void Animation::set_currentFrame(int new_currentFrame)
{
	currentFrame = new_currentFrame;
}

bool Animation::is_oneshot() const
{
	return oneshot;
}

void Animation::set_oneshot(bool new_oneshot)
{
	oneshot = new_oneshot;
}

float Animation::get_duration() const
{
	return dt*static_cast<float>(numFrames);
}

void Animation::set_duration(float new_duration) 
{
	dt = new_duration / static_cast<float>(numFrames);
}

bool Animation::is_finished() const
{
	return currentFrame == numFrames - 1;
}