#include "GLUtils.h"
#include <iostream>


GLuint GLUtils::LoadShader(GLenum shaderType, const char* shaderSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader != 0) {
        glShaderSource(shader, 1, &shaderSource, nullptr);
        glCompileShader(shader);

        GLint ret = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &ret);
        if (!ret) {
            char infoLog[512];
            glGetShaderInfoLog(shader, 512, nullptr, infoLog);
            std::cerr << "ERROR: Compile shader failed:\n " << infoLog << std::endl;

            glDeleteShader(shader);
            shader = 0;
        }

    }


    return shader;
}

GLuint GLUtils::CreateProgram(const char* vertexShaderSource, const char* fragmentShaderSource)
{
    GLuint vertexShader = LoadShader(GL_VERTEX_SHADER, vertexShaderSource);
    if (vertexShader == 0) {
        std::cerr << "create vertex shader failed" << std::endl;
        return 0;
    }

    GLuint fragmentShader = LoadShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
    if (fragmentShader == 0) {
        std::cerr << "create fragment shader failed" << std::endl;
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program != 0) {
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);
        glLinkProgram(program);

        GLint status = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &status);

        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        if (status != GL_TRUE) {
            char infoLog[512];
            glGetProgramInfoLog(program, 512, nullptr, infoLog);
            std::cerr << "ERROR: Link program failed:\n " << infoLog << std::endl;

            glDeleteProgram(program);
            program = 0;
        }
    }


    return program;
}

void GLUtils::DeletePrograme(GLuint program)
{
    if (program != 0) {
        GLint current = 0;
        glGetIntegerv(GL_CURRENT_PROGRAM, &current);
    
        if (current == program)
            glUseProgram(0);

        glDeleteProgram(program);
    }
}
