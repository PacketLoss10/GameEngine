#pragma once

#include "Component.h"
#include "Entity.h"
#include "vector"

template<typename T>
concept componenttype = std::is_base_of<Component, T>::value;

template<componenttype T>
class ComponentManager
{
protected:
	std::vector<T*> components;
public:
	void register_component(T* component)
	{
		components.push_back(component);
	}
	void despawn_components()
	{
		components.erase(
			std::remove_if(components.begin(), components.end(),
				[](T* component) {
					if (component->is_toDespawn())
					{
						component->set_toDespawn(false);
						return true;
					}
					return false;
				}
			), components.end()
		);
	}
	size_t get_components_count() const
	{
		return components.size();
	}
};