#pragma once

#include <string>

class Shader
{
private:

	// ID of program
	unsigned int ID;

	static void check_shader_compile_status(const unsigned int& shader, int& success, char* infoLog, const char* name = "\0");

	void check_link_status(int&success, char* infoLog)	const;

public:

	Shader(const char* vertexPath, const char* fragmentPath);

	// use/activate shader
	void use();

	// ID getter
	const int getID()	const;

	// uniform-funcs
	void setBool(const std::string& name, const bool value)	const;
	void setInt(const std::string& name, const int value)		const;
	void setFloat(const std::string& name, const float value)	const;

	~Shader() = default;

};
