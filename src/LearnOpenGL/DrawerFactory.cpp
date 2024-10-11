
#include "TriangleDrawer.h"
#include "RectangleDrawer.h"
#include "TextureDrawer.h"
#include "ThreeDimensionalDrawer.h"
#include "DrawerFactory.h"
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
	case TypeThreeDimensional:
		drawer = new ThreeDimensionalDrawer();
		break;
	default:
		break;
	}

    return drawer;
}
