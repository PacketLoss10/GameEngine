//#pragma once
//
//#include "Component.h"
//#include "Sprite.h"
//
//class AnimLayout
//{
//public:
//	IntVector start = IntVector(0, 0);
//	IntVector size = IntVector(1, 1);
//	AnimLayout() = default;
//	AnimLayout(IntVector start, IntVector size) :start(IntVector(std::max(0, start.x), std::max(0, start.y))), size(IntVector(std::max(1, size.x), std::max(1, size.y))) {}
//	operator sf::IntRect() const
//	{
//		return sf::IntRect(start, size);
//	}
//};
//
//class Animation :public Component
//{
//private:
//	Sprite* sprite;
//	AnimLayout layout = AnimLayout();
//	IntVector frameSize = IntVector();
//	int numFrames = 1;
//	int currentFrame = 0;
//	float dt = 0.f;
//	bool oneShot = false;
//	sf::Clock clock;
//	bool paused = false;
//public:
//	Animation(Entity* owner);
//	virtual ~Animation() = default;
//
//	void update();
//	void pause();
//	void play();
//	bool is_paused() const;
//	bool is_finished() const;
//};