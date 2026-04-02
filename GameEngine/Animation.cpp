//#include "Animation.h"
//#include "RenderComponentManager.h"
//
//Animation::Animation(Entity* owner) :Component(owner) 
//{
//}
//
//void Animation::update()
//{
//	sprite->set_relativeTransform(relativeTransform);
//
//	if (clock.getElapsedTime().asSeconds() < dt || paused || (oneShot && is_finished()))
//		return;
//
//	clock.restart();
//
//	currentFrame = (currentFrame + 1) % numFrames;
//
//	sprite->set_rect(TextureRect(
//		layout.start.component_wise_mult(frameSize) +
//		IntVector(
//			(currentFrame % layout.size.x) * frameSize.x,
//			(currentFrame / layout.size.x) * frameSize.y),
//		frameSize));
//}
//
//void Animation::pause()
//{
//	paused = true;
//}
//
//void Animation::play()
//{
//	paused = false;
//}
//
//bool Animation::is_paused() const
//{
//	return paused;
//}
//
//bool Animation::is_finished() const
//{
//	return currentFrame == numFrames - 1;
//}