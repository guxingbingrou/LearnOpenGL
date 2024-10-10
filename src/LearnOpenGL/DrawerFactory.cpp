#include "DrawerFactory.h"
#include "TriangleDrawer.h"
#include "RectangleDrawer.h"
#include "TextureDrawer.h"

IDrawer* DrawerFactory::CreateDrawer(DrawerType type)
{
	IDrawer* drawer = nullptr;
	switch (type)
	{
	case TypeTriangle:
		drawer = new TriangleDrawer();
		break;
	case TypeRectangle:
		drawer = new RectangleDrawer();
		break;
	case TypeTexture:
		drawer = new TextureDrawer();
		break;
	default:
		break;
	}

    return drawer;
}
