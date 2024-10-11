#pragma once
#include <string>
#include <GLFW/glfw3.h>
class IDrawer
{
public:
	virtual void PreperDrawer() = 0;
	virtual void Draw(int width, int height) = 0;
	virtual void AfterDraw() = 0;

	virtual void ProcessInput(GLFWwindow* window) = 0;
};

