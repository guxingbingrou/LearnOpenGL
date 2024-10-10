#pragma once
#include <glad/glad.h>

#define GLSL_STRINGIZE(x) #x
#define GLSL_STRINGIZE2(x) GLSL_STRINGIZE(x)
#define GLSL_STRING(x) GLSL_STRINGIZE2(x)


class GLUtils
{
public:
	static GLuint LoadShader(GLenum shaderType, const char* shaderSource);
	static GLuint CreateProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
	static void DeletePrograme(GLuint program);
};

