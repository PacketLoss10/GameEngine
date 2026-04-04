#pragma once

#include "ComponentManager.h"
#include "DragDropComponent.h"

#define DRAG_DROP_MANAGER DragDropManager::instance()

class DragDropManager :public ComponentManager<DragDropComponent>
{
private:
	DragDropManager() = default;
	DragDropManager(const DragDropManager&) = delete;
	DragDropManager& operator=(const DragDropManager&) = delete;

	DragDropComponent* hovered = nullptr;
	DragDropComponent* dragging = nullptr;
public:
	static DragDropManager& instance();
	void update();

	Entity* get_selected_entity() const;
	void set_dragged(DragDropComponent* comp);
};