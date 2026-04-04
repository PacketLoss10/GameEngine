#include "DragDropManager.h"
#include "InputHandler.h"

DragDropManager& DragDropManager::instance()
{
    static DragDropManager instance;
    return instance;
}

void DragDropManager::update()
{
	despawn_components();

    const Vector2& mousePos = INPUT.get_mouse_pos();

    DragDropComponent* newTopHovered = nullptr;
    int topLayer = INT_MIN;

    for (DragDropComponent* comp : components)
    {
        if (!comp || !comp->is_enabled())
            continue;

        CollisionComponent* geometry = comp->get_geometry();
        if (!geometry || !geometry->is_enabled() || !geometry->is_mouseOverlapping())
            continue;

        if (comp->get_layer() > topLayer)
        {
            topLayer = comp->get_layer();
            newTopHovered = comp;
        }
    }

    if (hovered != newTopHovered)
    {
        if (hovered)
        {
            hovered->on_hover_end.invoke();
        }
        if (newTopHovered)
        {
            newTopHovered->on_hover_begin.invoke();
        }
        hovered = newTopHovered;
    }

    if (hovered)
    {
        hovered->on_hover.invoke();
    }

    bool pressed = INPUT.is_button_pressed(Mouse::M1);
    bool held = INPUT.is_button_held(Mouse::M1);

    if (pressed && hovered && !dragging)
    {
        dragging = hovered;
        dragging->set_dragStartMousePos(mousePos);
        dragging->set_dragStartEntityPos(dragging->get_owner()->get_position());
        dragging->set_dragOffset(mousePos - dragging->get_dragStartEntityPos());
        dragging->on_drag_begin.invoke(mousePos);
    }

    if (dragging && held)
    {
        Vector2 targetPos = mousePos - dragging->get_dragOffset();
        if (dragging->is_draggable())
            dragging->get_owner()->set_position(targetPos);

        dragging->on_drag.invoke(mousePos);
    }

    if (dragging && !held)
    {
        dragging->on_drag_end.invoke(mousePos);
        dragging = nullptr;
    }
}

Entity* DragDropManager::get_selected_entity() const
{
    if (!hovered)
        return nullptr;

    return hovered->get_owner();
}

void DragDropManager::set_dragged(DragDropComponent* comp)
{
    dragging = comp;
}