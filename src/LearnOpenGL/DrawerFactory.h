#pragma once

#include "IDrawer.h"

enum DrawerType
{
	TypeTriangle = 0,
	TypeRectangle,
	TypeTexture,
};

class DrawerFactory
{
public:
	DrawerFactory() = default;
	static IDrawer* CreateDrawer(DrawerType type);
};

