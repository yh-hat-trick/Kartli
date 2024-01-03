
#include "GLEWGLFW.h"
#include "shader.h"
#include "Map.h"
#include "Texture.h"
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLFWwindow* window;
const int WIDTH = 1024;
const int HEIGHT = 768;

int vertexColorLocation = 0;

Map map;
Texture t;
Mesh m;

void init_window()
{
	if (!glfwInit())
	{
		std::cout << "ERROR::Failed to initialize GLFW3\n";
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	window = glfwCreateWindow(WIDTH, HEIGHT, "Kartli Test v69", NULL, NULL);
	if (!window)
	{
		std::cout << "ERROR::Failed to open GLFW window or init GL\n";
	}

	//init openGL
	glfwMakeContextCurrent(window);
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}
	std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

}

void run()
{
	Shader sha("mesh");
	sha.bind();
	t.bind(NULL);


	//transforms
	glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
	
	
	unsigned int transformLoc = glGetUniformLocation(sha.shaderID, "transform");
	std::cout << vec.x << vec.y << vec.z << std::endl;

	//vertexColorLocation = glGetUniformLocation(sha.shaderID, "ourcolor");
	//GAME LOOP
	while (!glfwWindowShouldClose(window))
	{
		//input
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}

		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 10.0f) + 0.5f;
		//std::cout << "\rGreenvalue: " << (greenValue) << ' ' << std::flush;
		
		//glUniform3f(vertexColorLocation, 0.0f, greenValue, 0.0f);
		glm::mat4 trans = glm::mat4(1.0f);
		trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		glClear(GL_COLOR_BUFFER_BIT);

		//t.bind(NULL);
		glBindVertexArray(m.vao);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}

int main()
{

	init_window();
	glClearColor(0.8,0.2,0.2,1);
	glViewport(0, 0, WIDTH, HEIGHT);

	//notice that WE have access to verts, and we give it to the GPU. The Mesh class does not have this.
	float verts[] = {
	//X		Y		Z	RGB
	-0.5f, -0.5f, 0.0f, 1.0f, 0, 0, 0.5, 1.0,
	 0.5f, -0.5f, 0.0f, 0, 1.0f, 0, 0.0, 0.0,
	 0.0f,  0.5f, 0.0f, 0, 0, 1.0f, 1.0f, 0.0
	};

	float square[] = {
	-0.5f, -0.5f, 0.0f, 1.0f, 0, 0, 0.5, 1.0,
	 0.5f, -0.5f, 0.0f, 0, 1.0f, 0, 0.0, 0.0,
	 0.5f,  0.5f, 0.0f, 0, 0, 1.0f, 1.0f, 0.0
	-0.5f,	0.5f, 0.0f, 1.0f, 0, 0, 0.5, 1.0,
	};

	float quadverts[] = {
	//X		Y		Z	R	 G	B  UV
	 0.5f,  0.5f, 0.0f, 1.0, 0, 0, 1.0, 1.0,  // top right
	 0.5f, -0.5f, 0.0f, 0, 1.0, 0, 1.0, 0,// bottom right
	-0.5f, -0.5f, 0.0f, 0, 0, 1.0, 0.0, 0.0,// bottom left
	-0.5f,  0.5f, 0.0f, 1.0, 1.0, 1.0, 0.0, 1.0 // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};

	//GPU loading code

	glGenVertexArrays(1, &m.vao);
	glGenBuffers(1, &m.vbo);
	glGenBuffers(1, &m.ebo);
	//bind them
	glBindVertexArray(m.vao);
	glBindBuffer(GL_ARRAY_BUFFER, m.vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadverts), quadverts, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m.ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//Vert are at attrib 0, comprised of 3 components of type GL_FLOAT, they are not normalized, each consecutive element is spaced 3 * 4 bytes (12) apart, and no offset
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(3 * sizeof(float)));
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (const void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	map.addMesh(m);
	t = Texture("wall.jpg");

	

	run();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}