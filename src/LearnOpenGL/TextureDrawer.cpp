#include "TextureDrawer.h"
#include "GLUtils.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

static const char* RESOURCE_DIR = "D:\\study\\VS2019Project\\LearnOpenGL\\resources";

static float vertices[]{
	//位置               颜色         纹理坐标
	0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 2.0f, 2.0f,  //右上角
	0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f, 0.0f, //右下角
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,//左下角
	-0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f //左上角
};

static unsigned int indices[] = {
	0, 1, 2,  //右下三角形
	0, 2, 3   //左上三角形
};

static const char vertexStr[] = GLSL_STRING(#version 330 core \n
	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec3 aColor;
	layout(location = 2) in vec2 aTexCoord;

	out vec3 ourColor;
	out vec2 TexCoord;

	uniform mat4 transform;

	void main() {
		gl_Position = transform * vec4(aPos, 1.0);
		ourColor = aColor;
		TexCoord = aTexCoord;
	}
);

static const char fragmentStr[] = GLSL_STRING(#version 330 core \n
	out vec4 FragColor;

	in vec3 ourColor;
	in vec2 TexCoord;

	uniform sampler2D texure1;
	uniform sampler2D texure2;
	uniform float mixValue;

	void main() {
		/*FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);*/
		FragColor = mix(texture(texure1, TexCoord), texture(texure2, TexCoord), mixValue);
		//FragColor = mix(texture(texure1, TexCoord), texture(texure2, vec2(1.0 - TexCoord.x, TexCoord.y)), 0.2);
	}
);


TextureDrawer::~TextureDrawer()
{
}

void TextureDrawer::PreperDrawer()
{
	LoadTexture();
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

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	m_texture_location[0] = glGetUniformLocation(m_program, "texure1");
	glUniform1i(m_texture_location[0], 0);

	m_texture_location[1] = glGetUniformLocation(m_program, "texure2");
	glUniform1i(m_texture_location[1], 1);

	m_mix_location = glGetUniformLocation(m_program, "mixValue");

	m_transform_location = glGetUniformLocation(m_program, "transform");

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void TextureDrawer::Draw(int width, int height)
{
	glUseProgram(m_program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture[1]);

	float timeValue = glfwGetTime();
	float mixValue = abs( sin(timeValue) );

	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
	trans = glm::rotate(trans, timeValue, glm::vec3(0.0, 0.0, 1.0));


	glUniformMatrix4fv(m_transform_location, 1, GL_FALSE, glm::value_ptr(trans));


	glUniform1f(m_mix_location, mixValue);

	glBindVertexArray(m_vao);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);


	trans = glm::mat4(1.0f);
	trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
	trans = glm::scale(trans, glm::vec3(mixValue, mixValue, 1.0));


	glUniformMatrix4fv(m_transform_location, 1, GL_FALSE, glm::value_ptr(trans));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	glBindVertexArray(0);
}

void TextureDrawer::AfterDraw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	GLUtils::DeletePrograme(m_program);
}

void TextureDrawer::LoadTexture()
{
	int width[2], height[2], nrChannels[2];

	unsigned char* data[2];

	stbi_set_flip_vertically_on_load(true);

	std::string path = std::string(RESOURCE_DIR) + "\\textures\\container.jpg";
	data[0] = stbi_load(path.c_str(), &width[0], &height[0], &nrChannels[0], 0);

	if (data[0]) {
		std::cout << "image(container.jpg) resolution: " << width[0] << "x" << height[0] << std::endl;
	}
	else {
		std::cerr << "failed to load image(container.jpg), path: " << path << std::endl;
		return;
	}

	path = std::string(RESOURCE_DIR) + "\\textures\\awesomeface.png";
	data[1] = stbi_load(path.c_str(), &width[1], &height[1], &nrChannels[1], 0);

	if (data[1]) {
		std::cout << "image(awesomeface.png) resolution: " << width[1] << "x" << height[1] << std::endl;
	}
	else {
		std::cerr << "failed to load image(awesomeface.png), path: " << path << std::endl;
		return;
	}

	glGenTextures(2, m_texture);


	glBindTexture(GL_TEXTURE_2D, m_texture[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[0], height[0], 0, GL_RGB, GL_UNSIGNED_BYTE, data[0]);

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data[0]);


	glBindTexture(GL_TEXTURE_2D, m_texture[1]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width[1], height[1], 0, GL_RGBA, GL_UNSIGNED_BYTE, data[1]);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data[1]);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void TextureDrawer::ProcessInput(GLFWwindow* window) {

}

void TextureDrawer::ProcessMouse(GLFWwindow* window, EventType type, float x, float y)
{
}
