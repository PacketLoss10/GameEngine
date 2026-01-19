#include "Animation.h"
#include "RenderComponentManager.h"

Animation::Animation(Entity* owner, bool enabled, Sprite sprite, AnimLayout layout, IVector frameSize, int numFrames, float fps, bool oneShot, bool autoStart) :Component(owner, enabled), Transformable(sprite.get_transform()), sprite(sprite), layout(layout), frameSize(frameSize), numFrames(std::max(1, numFrames)), dt(1.f / fps), oneShot(oneShot), paused(!autoStart) {}

Animation::Animation(Entity* owner, bool enabled, int zOrder, Transform transform, Texture texture, AnimLayout layout, IVector frameSize, int numFrames, float fps, bool oneShot, bool autoStart) :Component(owner, enabled), sprite(owner, enabled, texture, TextureRect(), zOrder, transform), layout(layout), frameSize(frameSize), numFrames(std::max(1, numFrames)), dt(1.f / fps), oneShot(oneShot), paused(!autoStart) {}

Animation::Animation(Entity* owner, bool enabled, int zOrder, Transform transform, Texture texture, NormalMap normal, AnimLayout layout, IVector frameSize, int numFrames, float fps, bool oneShot, bool autoStart) :Component(owner, enabled), sprite(owner, enabled, texture, TextureRect(), normal, zOrder, transform), layout(layout), frameSize(frameSize), numFrames(std::max(1, numFrames)), dt(1.f / fps), oneShot(oneShot), paused(!autoStart) {}

void Animation::init()
{
	RENDER_COMPONENT_MANAGER.register_component(&sprite);
}

void Animation::update()
{
	sprite.set_transform(transform);

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