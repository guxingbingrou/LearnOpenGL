#pragma once
#include "IDrawer.h"
#include <glad/glad.h>

class TriangleDrawer : public IDrawer
{
public:
	TriangleDrawer() = default;
	~TriangleDrawer();

	void PreperDrawer() override;
	void Draw() override;
	void AfterDraw() override;

private:
	GLuint m_vbo = 0;
	GLuint m_vao = 0;
	GLuint m_program = 0;

};

