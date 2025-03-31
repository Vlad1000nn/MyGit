//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include <iostream>
//#include <string>
//#include <algorithm>
//#include <cmath>
//
//#include "Camera.h"
//#include "Shader.h"
//
//const unsigned int SCREEN_WIDTH = 800;
//const unsigned int SCREEN_HEIGHT = 600;
//
//Camera camera;
//
//// time between last and curr frames
//float deltaTime = 0.0f;
//// time for last frame
//float lastFrame = 0.0f;
//
//
//// last postion of mouse
//float lastX = 400;
//float lastY = 300;
//
//
//float mixVal = 0.5f;
//float rotVal = 0.0f;
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
//	glViewport(0, 0, width, height);
//}
//
//// callback func to process mouse moves
//void mouse_callback(GLFWwindow* window, double xPos, double yPos) {
//	float x_offset = xPos - lastX;
//	float y_offset = lastY - yPos;
//	lastX = xPos;
//	lastY = yPos;
//	camera.rotate(x_offset, y_offset);
//}
//
//// mouse scroll callback
//void scroll_callback(GLFWwindow* window, double x_offset, double y_offset) {
//	camera.scroll((float)y_offset);
//}
//
//void processInput(GLFWwindow* window) {
//	// speed of camera
//	using enum CameraDirections;
//	bool is_slow = false;
//	// left_shift -> slow
//	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
//		is_slow = true;
//
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//	else if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
//		mixVal = std::max(0.0f, mixVal - 0.001f);
//	else if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
//		mixVal = std::min(1.0f, mixVal + 0.001f);
//	else if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
//		rotVal += 0.001f;
//	else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
//		rotVal -= 0.001f;
//	// cam moves
//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//		camera.move(FORWARD, deltaTime, (is_slow ? 0.2f : 1.0f));
//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//		camera.move(BACKWARD, deltaTime, (is_slow ? 0.2f : 1.0f));
//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//		camera.move(LEFT, deltaTime, (is_slow ? 0.2f : 1.0f));
//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//		camera.move(RIGHT, deltaTime, (is_slow ? 0.2f : 1.0f));
//}
//
//
//int main()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Window", NULL, NULL);
//	if (window == NULL) {
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glfwMakeContextCurrent(window);
//
//	// to avoid "jump" at the beginning of the program
//	double xPos, yPos;
//	glfwGetCursorPos(window, &xPos, &yPos);
//	lastX = xPos;
//	lastY = yPos;
//
//	// we capture cursor and its invisible
//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//	// set mouse callback
//	glfwSetCursorPosCallback(window, mouse_callback);
//	// set scroll mouse callback
//	glfwSetScrollCallback(window, scroll_callback);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		glfwTerminate();
//		return -1;
//	}
//
//	glm::vec4 vec2(1.0f, 0.0f, 0.0f, 1.0f);
//	glm::mat4 trans2 = glm::mat4(1.0f);
//	trans2 = glm::rotate(trans2, glm::radians(90.0f), glm::vec3(0.0, 0.0, 1.0));
//	trans2 = glm::scale(trans2, glm::vec3(0.5, 0.5, 0.5));
//
//	Shader shader("shaders/vertexShader.vert", "shaders/fragmentShader.frag");
//
//	float vertices[] = {
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//	};
//
//	glm::vec3 cubePositions[] = {
//	  glm::vec3(0.0f,  0.0f,  0.0f),
//	  glm::vec3(2.0f,  5.0f, -15.0f),
//	  glm::vec3(-1.5f, -2.2f, -2.5f),
//	  glm::vec3(-3.8f, -2.0f, -12.3f),
//	  glm::vec3(2.4f, -0.4f, -3.5f),
//	  glm::vec3(-1.7f,  3.0f, -7.5f),
//	  glm::vec3(1.3f, -2.0f, -2.5f),
//	  glm::vec3(1.5f,  2.0f, -2.5f),
//	  glm::vec3(1.5f,  0.2f, -1.5f),
//	  glm::vec3(-1.3f,  1.0f, -1.5f)
//	};
//
//	float indexes[] = {
//		0,1,3,
//		1,2,3
//	};
//
//	unsigned int VBO;
//	unsigned int VAO;
//	unsigned int EBO;
//
//	glGenBuffers(1, &VBO);
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), indexes, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBindVertexArray(0);
//
//	shader.use();
//
//	while (!glfwWindowShouldClose(window)) {
//		float currFrame = glfwGetTime();
//		deltaTime = currFrame - lastFrame;
//		lastFrame = currFrame;
//		processInput(window);
//
//		glClearColor(0.2f, 0.5f, 0.0f, 1.0f);
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//		shader.use();
//		glm::mat4 view = camera.getViewMatrix();
//
//		unsigned int viewLoc = glGetUniformLocation(shader.getID(), "view");
//		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
//
//		glm::mat4 proj = glm::perspective(glm::radians(camera.getFov()), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
//
//		unsigned int projLoc = glGetUniformLocation(shader.getID(), "proj");
//		glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
//
//
//		glBindVertexArray(VAO);
//		for (unsigned int cube = 0; cube < 10; ++cube) {
//			glm::mat4 model = glm::mat4(1.0f);
//			model = glm::translate(model, cubePositions[cube]);
//			const float angle = 20.0f * cube;
//			model = glm::rotate(model, glm::radians(50.0f + angle) * (float)glfwGetTime(), glm::vec3(1.0f, 0.3f, 0.5f));
//
//			unsigned int modelLoc = glGetUniformLocation(shader.getID(), "model");
//			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
//			glDrawArrays(GL_TRIANGLES, 0, 36);
//		}
//
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//
//	glfwTerminate();
//	return 0;
//}