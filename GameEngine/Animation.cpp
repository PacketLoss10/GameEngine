//#include "Animation.h"
//
//Animation::Animation() :RenderObject() {}
//
//Animation::Animation(std::string texturePath, IVector layout,IVector start, IVector frameSize, int numFrames, float fps, bool oneshot) 
//	:RenderObject(FrameData(texturePath, IRect(start, frameSize))), 
//	layout(IVector(std::max(1, layout.x), std::max(1, layout.y))), 
//	start(IVector(std::max(0, start.x), std::max(0, start.y))), 
//	numFrames(std::max(1, numFrames)), 
//	dt(1.f / fps),
//	oneshot(oneshot) {}
//
//void Animation::update() 
//{
//	if (clock.getElapsedTime().asSeconds() < dt)
//		return;
//
//	clock.restart();
//
//	if (oneshot && is_finished())
//		return;
//
//	currentFrame = (currentFrame + 1) % numFrames;
//
//	data.rect = IRect(
//		start.component_wise_mult(data.rect.size) +
//		IVector(
//			(currentFrame % layout.x) * data.rect.size.x,
//			(currentFrame / layout.x) * data.rect.size.y),
//		data.rect.size);
//}
//
//void Animation::set_currentFrame(int new_currentFrame) 
//{
//	currentFrame = new_currentFrame;
//}
//
//void Animation::set_duration(float new_duration) 
//{
//	dt = 1.f / (static_cast<float>(numFrames) / new_duration);
// 
// 
//}
//
//bool Animation::is_finished() const 
//{ 
//	return currentFrame == numFrames - 1;
//}
#include "Animation.h"

Animation::Animation() :Sprite(), layout(IVector(0, 0), IVector(1, 1)), numFrames(1), currentFrame(0), dt(0.f), oneshot(false) {}

Animation::Animation(std::string texture, IVector frameSize, std::string normalMap, IRect layout, int numFrames, float fps, float oneshot)
	:Sprite(texture, IRect(layout.position, IVector(std::max(0, frameSize.x), std::max(0, frameSize.y))), normalMap),
	layout(IRect(IVector(std::max(0, layout.position.x), std::max(0, layout.position.y)), IVector(std::max(1, layout.size.x), std::max(1, layout.size.y)))),
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
		layout.position.component_wise_mult(rect.size) +
		IVector(
			(currentFrame % layout.size.x) * rect.size.x,
			(currentFrame / layout.size.x) * rect.size.y),
		rect.size);
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