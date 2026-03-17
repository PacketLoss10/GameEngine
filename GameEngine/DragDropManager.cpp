#include "DragDropManager.h"

DragDropManager& DragDropManager::instance()
{
	static DragDropManager instance;
	return instance;
}
