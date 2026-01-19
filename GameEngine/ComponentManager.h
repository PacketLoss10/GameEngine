#pragma once

#include "Component.h"
#include "Entity.h"
#include "vector"

template<typename T>
concept IsComponent = std::is_base_of<Component, T>::value;

template<IsComponent T>
class ComponentManager
{
protected:
	std::vector<T*> components;
	bool debugMode = false;
public:
	void register_component(T* component)
	{
		components.push_back(component);
	}
	void delete_components()
	{
		components.erase(
			std::remove_if(components.begin(), components.end(),
				[](T* component)
				{
					return !component;
				}
			), components.end()
		);
	}
	void enable_debug()
	{
		debugMode = true;
	}
	void disable_debug()
	{
		debugMode = false;
	}
};