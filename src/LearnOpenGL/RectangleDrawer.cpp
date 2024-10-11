#include "RectangleDrawer.h"
#include "GLUtils.h"
#include <iostream>
#include <GLFW/glfw3.h>

static float vertices[]{
	0.5f, 0.5f, 0.0f,  //右上角
	0.5f, -0.5f, 0.0f, //右下角
	-0.5f, -0.5f, 0.0f, //左下角
	-0.5f, 0.5f, 0.0f  //左上角
};

static unsigned int indices[] = {
	0, 1, 2,  //右下三角形
	0, 2, 3   //左上三角形
};

static const char vertexStr[] = GLSL_STRING(#version 330 core \n
	layout(location = 0) in vec3 aPos;

	void main() {
		gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);
	}
);

static const char fragmentStr[] = GLSL_STRING(#version 330 core \n
	out vec4 FragColor;
	uniform vec4 ourColor;

	void main() {
		FragColor = ourColor;
	}
);


RectangleDrawer::~RectangleDrawer()
{
}

void RectangleDrawer::PreperDrawer()
{
	//use vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	m_program = GLUtils::CreateProgram(vertexStr, fragmentStr);
	if (m_program == 0) {
		std::cerr << "create program failed" << std::endl;
		return;
	}
	glUseProgram(m_program);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	m_color_location = glGetUniformLocation(m_program, "ourColor");

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void RectangleDrawer::Draw(int width, int height)
{
	glUseProgram(m_program);
	glBindVertexArray(m_vao);

	float timeValue = glfwGetTime();
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	glUniform4f(m_color_location, 0.0f, greenValue, 0.0f, 1.0f);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	
	glBindVertexArray(0);
}

void RectangleDrawer::AfterDraw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	GLUtils::DeletePrograme(m_program);
}

void RectangleDrawer::ProcessInput(GLFWwindow* window) {

}