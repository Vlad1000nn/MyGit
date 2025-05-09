#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ProjectSettings.h"
#include "Shader.h"
#include "Camera.h"

#include <stdexcept>
#include <iostream>
#include <vector>

float delta_time = 0.0f;
float last_frame = 0.0f;

float last_x = 640.0f;
float last_y = 360.0f;

// added camera control (to get a better look)
Camera camera;

// Initialize glfw (OPENGL_3_3) + create Window
GLFWwindow* createWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "lab1_window", NULL, NULL);
	if (window == NULL)
		throw std::runtime_error("Failed to create GLFW window");

	return window;
}

void framebufferSizeCallback(GLFWwindow* window, const int width, const int height) {
	glViewport(0, 0, width, height);
}

void mouseCallback(GLFWwindow* window, const double x_pos, const double y_pos) {
	float x_offset = (float)x_pos - last_x;
	float y_offset = last_y - (float)y_pos;
	last_x = (float)x_pos;
	last_y = (float)y_pos;
	camera.rotate(x_offset, y_offset);
}

void scrollCallback(GLFWwindow* window, const double x_offset, const double y_offset) {
	camera.scroll((float)y_offset);
}

void inputProcessing(GLFWwindow* window) {
	const float base_speed_coef = 1.0f;
	const float slow_speed_coef = 0.2f;

	using enum CameraDirections; // C++ 20
	bool is_slow = false;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		is_slow = true;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.move(FORWARD, delta_time, (is_slow ? slow_speed_coef : base_speed_coef));
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.move(BACKWARD, delta_time, (is_slow ? slow_speed_coef : base_speed_coef));
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.move(LEFT, delta_time, (is_slow ? slow_speed_coef : base_speed_coef));
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.move(RIGHT, delta_time, (is_slow ? slow_speed_coef : base_speed_coef));
}


int main()
{
	GLFWwindow* window = NULL;
	try {
		window = createWindow();
		glfwMakeContextCurrent(window);

		{	// get start position of cursor
			double x_pos, y_pos;
			glfwGetCursorPos(window, &x_pos, &y_pos);
			last_x = (float)x_pos;
			last_y = (float)y_pos;
		}
		// cursor capture(to close window use ESCAPE)
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
		glfwSetCursorPosCallback(window, mouseCallback);
		glfwSetScrollCallback(window, scrollCallback);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("Failed to initialize GLAD");
	}
	catch (std::runtime_error& e) {
		std::cerr << "RE:" << e.what() << std::endl;
		glfwTerminate();
		return -1;
	}

	// start position of camera
	const glm::vec3 start_pos = glm::vec3(20.0f, 20.0f, 20.0f);
	// target of camera
	const glm::vec3 target_pos = glm::vec3(0.0f, 0.0f, 0.0f);

	camera.setPos(start_pos);
	camera.setFront(glm::normalize(target_pos - start_pos));
	camera.setRight(glm::normalize(glm::cross(camera.getFront(), camera.getWorldUp())));

	camera.setPitch(glm::degrees(glm::asin(camera.getFront().y)));

	const glm::vec3 front_proj = glm::normalize(glm::vec3(camera.getFront().x, 0.0f, camera.getFront().z));
	camera.setYaw(glm::degrees(glm::atan(front_proj.z, front_proj.x)));

	camera.confirm_settings();

	Shader shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");

	const std::vector<float> condition = {
		3.0f,  3.0f,  1.0f, 0.0f,  0.0f,
		-1.0f, 2.0f,  0.0f, 1.0f,  0.0f,
		0.0f,  -0.5f, 0.0f, 0.0f,  1.0f,
		2.0f,  2.0f,  1.0f, 1.0f, 1.0f
	};

	// divide to triangles
	const unsigned int indexes[] = {
		0, 1, 3,
		1, 2, 3
	};
	const int condition_size = (int)condition.size();

	glm::vec3 normal = glm::vec3(1.0f);
	{
		glm::vec3 point1 = glm::vec3(condition[0], 0.0f, condition[1]);
		glm::vec3 point2 = glm::vec3(condition[2], 0.0f, condition[3]);
		normal = glm::normalize(glm::cross(point1, point2));
	}

	std::vector<float> vertices;
	for (int i = 0; i < condition_size; i += 5) {
		// coords
		vertices.push_back(condition[i]);
		vertices.push_back(0.0f);
		vertices.push_back(condition[i+1]);
		// normal's coords
		vertices.push_back(normal.x);
		vertices.push_back(std::abs(normal.y)); 
		vertices.push_back(normal.z);
		// colors
		vertices.push_back(condition[i + 2]);
		vertices.push_back(condition[i + 3]);
		vertices.push_back(condition[i + 4]);
	}

	unsigned int VBO;
	unsigned int VAO;
	unsigned int EBO;

	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * (int)vertices.size(), vertices.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	float curr_frame;
	const float background_color[4] = { 0.1f, 0.1f, 0.1f, 1.0f };

	glm::mat4 view, proj;
	glm::mat4 model = glm::mat4(1.0f);

	// material settings
	const glm::vec3 ambient = glm::vec3(1.0f, 0.5f, 0.31f);
	const glm::vec3 diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
	const glm::vec3 specular = glm::vec3(0.5f, 0.5f, 0.5f);
	const float shininess = 64.0f;

	// light settings
	const glm::vec3 l_ambient = glm::vec3(0.5f, 0.5f, 0.5f);
	const glm::vec3 l_diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	const glm::vec3 l_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	const glm::vec3 light_direction = glm::vec3(-1.0f, -1.0f, -1.0f); // parallel (1,1,1)
	const glm::vec3 light_color = glm::vec3(1.0f, 1.0f, 1.0f);

	shader.use();

	// material set up
	shader.setVec3f("material.ambient", ambient);
	shader.setVec3f("material.diffuse", diffuse);
	shader.setVec3f("material.specular", specular);
	shader.setFloat("material.shininess", shininess);

	// Light Set up
	glm::vec3 diffuseColor = light_color * l_ambient;
	glm::vec3 ambientColor = diffuseColor * l_diffuse;

	shader.setVec3f("light.direction", light_direction);
	shader.setVec3f("light.ambient", ambientColor);
	shader.setVec3f("light.diffuse", diffuseColor);
	shader.setVec3f("light.specular", l_specular);

	while (!glfwWindowShouldClose(window)) {
		curr_frame = (float)glfwGetTime();
		delta_time = curr_frame - last_frame;
		last_frame = curr_frame;
		inputProcessing(window);

		glClearColor(background_color[0], background_color[1], background_color[2], background_color[3]);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBindVertexArray(0);

		shader.use();

		view = camera.getViewMatrix();
		proj = glm::perspective(glm::radians(camera.getFov()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);

		shader.setMat4f("view", view);
		shader.setMat4f("proj", proj);
		shader.setMat4f("model", model);

		shader.setVec3f("viewPos", camera.getPos());

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &EBO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();

	return 0;
}