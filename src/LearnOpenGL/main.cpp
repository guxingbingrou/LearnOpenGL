#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include "DrawerFactory.h"



static int s_width = 800;
static int s_height = 600;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	std::cout << "framebuffer_size_callback: " << width << "x" << height << std::endl;
	s_width = width;
	s_height = height;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main() {
	//auto drawer = std::unique_ptr<IDrawer>(DrawerFactory::CreateDrawer(TypeTriangle));
	//auto drawer = std::unique_ptr<IDrawer>(DrawerFactory::CreateDrawer(TypeRectangle));
	//auto drawer = std::unique_ptr<IDrawer>(DrawerFactory::CreateDrawer(TypeTexture));
	auto drawer = std::unique_ptr<IDrawer>(DrawerFactory::CreateDrawer(TypeThreeDimensional));

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(s_width, s_height, "LearnOpenGL", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glViewport(0, 0, s_width, s_height);

	
	drawer->PreperDrawer();

	while (!glfwWindowShouldClose(window))
	{
		//´¦ÀíÊäÈë
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//äÖÈ¾
		drawer->Draw(s_width, s_height);


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	drawer->AfterDraw();



	glfwTerminate();


	return 0;
}

