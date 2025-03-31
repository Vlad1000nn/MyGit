#pragma once

#include <string>
#include <glm/glm.hpp>

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
	void setVec2f(const std::string& name, const float value1, const float value2)	const;
	void setVec2f(const std::string& name, const glm::vec2& value)	const;
	void setVec3f(const std::string& name, const float value1, const float value2, const float value3)	const;
	void setVec3f(const std::string& name, const glm::vec3& value)	const;
	void setVec4f(const std::string& name, const glm::vec4& value)	const;
	void setVec4f(const std::string& name, const float value1, const float value2, const float value3, const float value4)	const;

	void setMat2f(const std::string& name, const glm::mat2& value)	const;
	void setMat3f(const std::string& name, const glm::mat3& value)	const;
	void setMat4f(const std::string& name, const glm::mat4& value)	const;

	~Shader() = default;

};
