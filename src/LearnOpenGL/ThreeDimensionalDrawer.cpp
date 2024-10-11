#include "ThreeDimensionalDrawer.h"
#include "GLUtils.h"
#include <iostream>
#include <GLFW/glfw3.h>


#define STB_IMAGE_STATIC
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

static const char* RESOURCE_DIR = "D:\\study\\VS2019Project\\LearnOpenGL\\resources";

static float vertices[]{
	        //位置              纹理坐标
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

static unsigned int indices[] = {
	0, 1, 2,  //右下三角形
	0, 2, 3   //左上三角形
};

static const char vertexStr[] = GLSL_STRING(#version 330 core \n
	layout(location = 0) in vec3 aPos;
	layout(location = 1) in vec2 aTexCoord;

	out vec2 TexCoord;

	uniform mat4 model;
	uniform mat4 view;
	uniform mat4 projection;

	void main() {
		gl_Position = projection * view * model * vec4(aPos, 1.0);
		TexCoord = aTexCoord;
	}
);

static const char fragmentStr[] = GLSL_STRING(#version 330 core \n
	out vec4 FragColor;

	in vec2 TexCoord;

	uniform sampler2D texure1;
	uniform sampler2D texure2;

	void main() {
		FragColor = mix(texture(texure1, TexCoord), texture(texure2, TexCoord), 0.2);
	}
);

ThreeDimensionalDrawer::ThreeDimensionalDrawer():
	m_camera_pos(0.0f, 0.0f, 3.0f),
	m_camera_front(0.0f, 0.0f, -1.0f),
	m_camera_up(0.0f, 1.0f, 0.0f)
{

}

ThreeDimensionalDrawer::~ThreeDimensionalDrawer()
{
}

void ThreeDimensionalDrawer::PreperDrawer()
{
	LoadTexture();
	//use vao
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//glGenBuffers(1, &m_ebo);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	m_program = GLUtils::CreateProgram(vertexStr, fragmentStr);
	if (m_program == 0) {
		std::cerr << "create program failed" << std::endl;
		return;
	}
	glUseProgram(m_program);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	m_texture_location[0] = glGetUniformLocation(m_program, "texure1");
	glUniform1i(m_texture_location[0], 0);

	m_texture_location[1] = glGetUniformLocation(m_program, "texure2");
	glUniform1i(m_texture_location[1], 1);

	m_model_location = glGetUniformLocation(m_program, "model");

	m_view_location = glGetUniformLocation(m_program, "view");

	m_projection_location = glGetUniformLocation(m_program, "projection");

	glEnable(GL_DEPTH_TEST);

	glUseProgram(0);
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

}

void ThreeDimensionalDrawer::Draw(int width, int height)
{
	glUseProgram(m_program);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_texture[1]);

	glm::vec3 cubePositions[] = {
		  glm::vec3(0.0f,  0.0f,  0.0f),
		  glm::vec3(2.0f,  5.0f, -15.0f),
		  glm::vec3(-1.5f, -2.2f, -2.5f),
		  glm::vec3(-3.8f, -2.0f, -12.3f),
		  glm::vec3(2.4f, -0.4f, -3.5f),
		  glm::vec3(-1.7f,  3.0f, -7.5f),
		  glm::vec3(1.3f, -2.0f, -2.5f),
		  glm::vec3(1.5f,  2.0f, -2.5f),
		  glm::vec3(1.5f,  0.2f, -1.5f),
		  glm::vec3(-1.3f,  1.0f, -1.5f)
	};
	
	glBindVertexArray(m_vao);

	for (int i = 0; i < 10; ++i) {
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, cubePositions[i]);

		float timeValue = glfwGetTime();

		if(i % 3 == 0)
			model = glm::rotate(model, timeValue, glm::vec3(1.0f, 1.0f, 1.0f));

		glUniformMatrix4fv(m_model_location, 1, GL_FALSE, glm::value_ptr(model));

		glm::mat4 view = glm::mat4(1.0f);
		//float radius = 10.0f;
		//float camX = sin(timeValue) * radius;
		//float camZ = cos(timeValue) * radius;
		//view = glm::lookAt(glm::vec3(camX, 0.0f, camZ), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		view = glm::lookAt(m_camera_pos, m_camera_pos + m_camera_front, m_camera_up);


		glUniformMatrix4fv(m_view_location, 1, GL_FALSE, glm::value_ptr(view));

		glm::mat4 projection = glm::mat4(1.0f);
		projection = glm::perspective(glm::radians(45.0f), width * 1.0f / height, 0.1f, 100.0f);

		glUniformMatrix4fv(m_projection_location, 1, GL_FALSE, glm::value_ptr(projection));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}




	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);


	glBindVertexArray(0);
}

void ThreeDimensionalDrawer::AfterDraw()
{
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glDisable(GL_DEPTH_TEST);
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	//glDeleteBuffers(1, &m_ebo);
	GLUtils::DeletePrograme(m_program);
}

void ThreeDimensionalDrawer::LoadTexture()
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

void ThreeDimensionalDrawer::ProcessInput(GLFWwindow* window) {
	float cameraSpeed = 0.05f;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_camera_pos += m_camera_front * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_camera_pos -= m_camera_front * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		m_camera_pos -= glm::normalize(glm::cross(m_camera_front, m_camera_up))  * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		m_camera_pos += glm::normalize(glm::cross(m_camera_front, m_camera_up)) * cameraSpeed;
}