#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true); 
}

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"\n"
"void main()\n"
"{"
"FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";


int main()
{
	glfwInit(); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "My Window", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Create shader object of vertex shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// bind our shader settings and compile
	// args: 1 - shader object, 2 - count of lines, 3 - source code, 4 - skip
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// If doesn't compile we check it and output message error
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION::FAILED::\n" << infoLog << std::endl;
	}

	// Do the same with fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION::FAILED::\n" << infoLog << std::endl;
	}

	// Now create shader program (final program with shader sequence)
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	// attach shaders to program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// link all this shaders
	glLinkProgram(shaderProgram);

	// Check is all good or not
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINK::ERROR::\n" << infoLog << std::endl;
	}

	// Delete shaders bcs we don't need them anymore
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Normalized coords of vertexes (unique)
	float vertices[] = {
		0.5f,  0.5f, 0.0f,  
		0.5f, -0.5f, 0.0f,  
		-0.5f, -0.5f, 0.0f,  
		-0.5f,  0.5f, 0.0f   
	};

	// Indexes of triangles
	unsigned int indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3 // second triangle
	};

	// Element Buffer Objects (buffer, that stores indexes of openGL, that need to draw)
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// Vertex Buffer Object (to storage data in gpu and manage it)
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	
	// Vertex Array Object (contains pointers to VBO, indexes Buffer, to link data from buffer with vertex attributes)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// first attach VAO
	glBindVertexArray(VAO);

	// Bind VBO to GL_ARRAY_BUFFER, it means that now every buffer call of GL_A_B will use for VBO too 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Copy vertices to buffer to draw it
	// GL_STATIC_DRAW - data specified 1 time and use by CPU no more than few times
	// GL_STREAM_DRAW - data specified 1 time and use many times
	// GL_DYNAMIC_DRAW - data often changing and use many times
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Now we need to set up how to put data in vertex buffer
	// args: 1 - which vertex attribute we want configure,	(we point that layout = 0, so we pass 0)
	// 2 - size of vertex buffer (we have vec3, so pass 3)
	// 3 - data type; 4 - should we normalize our data?
	// 5 - size of stride(step) between 2 vertex attributes (we could pass 0 bcs our data tightly packed and glfw can
	// determine it by himself)
	// 6 - offset(when our data begins). Now vertex attribute 0 attached with our VBO (bcs we link VBO and GL_ARRAY_BUFFER)	
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
		
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBindVertexArray(0);
	
	// funcs to draw lines excepts filled figures
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window)) {
		processInput(window);
		glClearColor(0.2f, 0.5f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		// Draw func, args: 1 - mode, 2 - start index of VAO, count of vertexes to draw
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 7, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		glfwSwapBuffers(window); 
		glfwPollEvents();
	}

	// Free recources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	glfwTerminate();
	return 0;
}