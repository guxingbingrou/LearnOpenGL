#pragma once

#include "IDrawer.h"

enum DrawerType
{
	TypeTriangle = 0
};

class DrawerFactory
{
public:
	DrawerFactory() = default;
	static IDrawer* CreateDrawer(DrawerType type);
};
