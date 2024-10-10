#include "DrawerFactory.h"
#include "TriangleDrawer.h"

IDrawer* DrawerFactory::CreateDrawer(DrawerType type)
{
	IDrawer* drawer = nullptr;
	switch (type)
	{
	case TypeTriangle:
		drawer = new TriangleDrawer();
		break;
	default:
		break;
	}

    return drawer;
}
