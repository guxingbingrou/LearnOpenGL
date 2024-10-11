#pragma once
#include "IDrawer.h"
#include <glad/glad.h>
class ThreeDimensionalDrawer : public IDrawer
{
public:
	ThreeDimensionalDrawer() = default;
	~ThreeDimensionalDrawer();

	void PreperDrawer() override;
	void Draw(int width, int height) override;
	void AfterDraw() override;

private:
	void LoadTexture();
	GLuint m_vbo = 0;
	GLuint m_vao = 0;
	//GLuint m_ebo = 0;
	GLuint m_program = 0;
	GLuint m_texture[2] = { 0 };

	GLint m_texture_location[2] = { 0 };
	GLint m_model_location = 0;
	GLint m_view_location = 0;
	GLint m_projection_location = 0;
};

