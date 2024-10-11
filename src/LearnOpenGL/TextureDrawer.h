#pragma once
#include "IDrawer.h"
#include <glad/glad.h>
class TextureDrawer : public IDrawer
{
public:
	TextureDrawer() = default;
	~TextureDrawer();

	void PreperDrawer() override;
	void Draw(int width, int height) override;
	void AfterDraw() override;

private:
	void LoadTexture();
	GLuint m_vbo = 0;
	GLuint m_vao = 0;
	GLuint m_ebo = 0;
	GLuint m_program = 0;
	GLuint m_texture[2] = { 0 };

	GLint m_texture_location[2] = { 0 };
	GLint m_mix_location = 0;
	GLint m_transform_location = 0;
};

