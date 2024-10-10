#pragma once
#include "IDrawer.h"
#include <glad/glad.h>
class RectangleDrawer : public IDrawer
{
public:
	RectangleDrawer() = default;
	~RectangleDrawer();

	void PreperDrawer() override;
	void Draw() override;
	void AfterDraw() override;

private:
	GLuint m_vbo = 0;
	GLuint m_vao = 0;
	GLuint m_ebo = 0;
	GLuint m_program = 0;

	GLint m_color_location = 0;
};

