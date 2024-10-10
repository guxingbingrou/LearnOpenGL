#pragma once
class IDrawer
{
public:
	virtual void PreperDrawer() = 0;
	virtual void Draw() = 0;
	virtual void AfterDraw() = 0;
};

