#include "InputHandler.h"
#include "Renderer.h"
#include "WorldSystem.h"
#include "CircleCollision.h"

class AAA :public Actor
{
	SETUP_ACTOR(AAA)

	void update() override {}
public:
	AAA() :Actor(Transform()) 
	{
		collision = new CircleCollision(50.f, FVector(0.f, 0.f), Color(0, 0, 0, 0), Color(255, 255, 255, 255), true);
		on_overlap.bind(this, &AAA::test_function);
	}

	void test_function(const Actor* actor, const Actor* other) 
	{
		std::cout << "test_function called" << std::endl;
		return; 
	}
};

int main()
{
	AAA a;
	AAA b;

	if(a.get_collision()->is_overlapping(b.get_collision()))
	{
		a.on_overlap.invoke(&a, &b);
	}

	return 0;
}