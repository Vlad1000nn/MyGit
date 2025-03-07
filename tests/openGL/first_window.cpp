#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// callback function, calls when window changed size. Need to change viewport
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// viewport -> what user see in the main window; args 1,2 is coords of left down corner, 3,4 - width, height
	glViewport(0, 0, width, height);
}

// traking the input
void processInput(GLFWwindow* window) {
	// 1 arg is object of input, 2 arg is key (return GLFW_PRESS if true, otherwise GLFW_RELEASE
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true); // set true to WindowShouldClo	se to the window
}

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

int main()
{
	glfwInit(); // Initialization of glfw

	// glfwWindowHint, 1 argument - what to set up,  2 arg - value we set
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// In fact, we said to use OPENGL 3.3

	// Use core-profile (delete old funcs, necessary use shaders, good perfomance, easy to dev)
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Window", NULL, NULL);
	// If window wasn't created
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Now window is current context
	glfwMakeContextCurrent(window);
	// Say to glfw that we have framebuffer_size_callback function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	// NOTE: registration of callback funcs should be AFTER window creating and BEFORE rendering cycle

	// GLAD operates with pointers, so only after init we can use opengl funcs
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// rendering cycle
	while (!glfwWindowShouldClose(window)) {
		// check the input every frame(iter)
		processInput(window);
		// set rgba color to clear
		glClearColor(0.8f, 0.5f, 0.0f, 1.0f);
		// clear color buffer (GL_COLOR_BUFFER_BIT -> color buffer, GL_DEPTH_BUFFER_BIT -> depth buffer,
		// GL_STENCIL_BUFFER_BIT -> stencil buffer)
		glClear(GL_COLOR_BUFFER_BIT);

		// swap 2d color buffer(contain colors for each pixel in window), which is using for rendering for curr iter and draw it 
		glfwSwapBuffers(window); 
		// watch for events, update window state and call callback funcs
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}