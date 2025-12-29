#include "InputHandler.h"
#include "Renderer.h"
#include "WorldSystem.h"

class AAA :public Actor
{
	void update() override {}
public:
	AAA() :Actor(Transform()) {}
};
class BBB :public Actor
{
	void update() override {}
public:
	BBB() :Actor(Transform()) {}
};


int main()
{
	WORLD.spawn_entity(std::make_unique<AAA>());
	WORLD.spawn_entity(std::make_unique<BBB>());
	std::cout << WORLD.find_all_objects_of_type<AAA, BBB>().size();
	return 0;
}