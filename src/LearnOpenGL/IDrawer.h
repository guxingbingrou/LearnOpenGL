#pragma once
#include <string>
#include <GLFW/glfw3.h>

enum EventType
{
	TYPE_DOWN = 0,
	TYPE_UP,
	TYPE_MOVE,
	TYPE_SCROLL
};

class IDrawer
{
public:
	virtual void PreperDrawer() = 0;
	virtual void Draw(int width, int height) = 0;
	virtual void AfterDraw() = 0;

	virtual void ProcessInput(GLFWwindow* window) = 0;
	virtual void ProcessMouse(GLFWwindow* window, EventType type, float x, float y) = 0;
};

