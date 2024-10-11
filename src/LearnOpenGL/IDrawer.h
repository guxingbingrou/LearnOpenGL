#pragma once
#include <string>
class IDrawer
{
public:
	virtual void PreperDrawer() = 0;
	virtual void Draw(int width, int height) = 0;
	virtual void AfterDraw() = 0;
};

