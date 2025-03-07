#include "Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>



Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// step 1: read
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream;
		std::stringstream fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();

		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Shader Error, file not succesfully read" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// step 2: compile

	unsigned int vertexShader;
	unsigned int fragmentShader;
	int success;
	char infoLog[512];

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);
	check_shader_compile_status(vertexShader, success, infoLog, "Vertex");

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);
	check_shader_compile_status(fragmentShader, success, infoLog, "Fragment");

	// step 3: link
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);
	check_link_status(success, infoLog);

	// step 4: delete shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

void Shader::check_shader_compile_status(const unsigned int& shader, int& success, char* infoLog, const char* name) 
{
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << (name == "\0" ? " " : name) << "shader compile error:\n" << infoLog << std::endl;
	}
}

void Shader::check_link_status(int& success,char* infoLog)	const
{
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "Shader program link error:\n" << infoLog << std::endl;
	}
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name,const bool value)	const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setInt(const std::string& name, const int value)	const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, const float value)	const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

const int Shader::getID()	const
{
	return ID;
}
