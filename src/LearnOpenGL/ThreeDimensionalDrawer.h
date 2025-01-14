#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "IDrawer.h"
class ThreeDimensionalDrawer : public IDrawer
{
public:
	ThreeDimensionalDrawer();
	~ThreeDimensionalDrawer();

	void PreperDrawer() override;
	void Draw(int width, int height) override;
	void AfterDraw() override;
	void ProcessInput(GLFWwindow* window) override;
	void ProcessMouse(GLFWwindow* window, EventType type, float x, float y) override;

private:
	void LoadTexture();
	void ProcessMouseCursor(GLFWwindow* window, float x, float y);
	void ProcessMouseScroll(GLFWwindow* window, float x, float y);
	int m_width = 800;
	int m_height = 600;
	GLuint m_vbo = 0;
	GLuint m_vao = 0;
	//GLuint m_ebo = 0;
	GLuint m_program = 0;
	GLuint m_texture[2] = { 0 };

	GLint m_texture_location[2] = { 0 };
	GLint m_model_location = 0;
	GLint m_view_location = 0;
	GLint m_projection_location = 0;

	glm::vec3 m_camera_pos;
	glm::vec3 m_camera_front;
	glm::vec3 m_camera_up;
	float m_fov = 45.0f;
	
};

