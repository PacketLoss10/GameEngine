#pragma once

#include "Component.h"
#include "Entity.h"

template<typename T>
concept IsComponent = std::is_base_of<Component, T>::value;

template<IsComponent T>
class ComponentManager
{
protected:
	std::vector<T*> components;
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
					if (component->is_toDelete() || !component->get_owner())
					{
						delete component;
						return true;
					}
					return false;
				}
			), components.end()
		);
	}
};