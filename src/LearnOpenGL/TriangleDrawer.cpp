#include "TriangleDrawer.h"
#include "GLUtils.h"
#include <iostream>
#include <GLFW/glfw3.h>

static float vertices[]{
	//Î»ÖÃ                  //ÑÕÉ«
	-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
};

static const char vertexStr[] = GLSL_STRING(#version 330 core \n
	layout (location = 0) in vec3 aPos; 
	layout (location = 1) in vec3 aColor;
	out vec3 ourColor;
	uniform vec2 offset;
	void main() { 
		gl_Position = vec4(aPos.x + offset.x, aPos.y + offset.y, aPos.z, 1.0f);
		ourColor = vec3(aColor.x + offset.x, aColor.y + offset.x, aColor.z + offset.x);
	}
);

static const char fragmentStr[] = GLSL_STRING(#version 330 core \n
	out vec4 FragColor;
	in vec3 ourColor;
	void main() {
		FragColor = vec4(ourColor, 1.0f);
	}
);


TriangleDrawer::~TriangleDrawer()
{
}

void TriangleDrawer::PreperDrawer()
{
	//use vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	m_program = GLUtils::CreateProgram(vertexStr, fragmentStr);
	if (m_program == 0) {
		std::cerr << "create program failed" << std::endl;
		return;
	}
	glUseProgram(m_program);
	m_offset_location = glGetUniformLocation(m_program, "offset");

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);


}

void TriangleDrawer::Draw(int width, int height)
{
	glUseProgram(m_program);
	glBindVertexArray(m_vao);

	float timeValue = glfwGetTime();
	float x_offset = sin(timeValue) / 2.0f;
	float y_offset = cos(timeValue) / 2.0f;
	glUniform2f(m_offset_location, x_offset, y_offset);

	glDrawArrays(GL_TRIANGLES, 0, 3);
	glBindVertexArray(0);
}

void TriangleDrawer::AfterDraw()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	GLUtils::DeletePrograme(m_program);
}
