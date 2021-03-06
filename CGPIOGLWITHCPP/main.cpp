#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include "Utils.h"
using namespace std;

const int NUMBER_OF_VERTEX_ARRAY_OBJECTS = 1;
const int NUMBER_OF_VERTEX_BUFFER_OBJECTS = 2;

float cameraX;
float cameraY;
float cameraZ;

float cubeLocationX;
float cubeLocationY;
float cubeLocationZ;

int width;
int height;
float aspect;

//Matrix4GLF perspectiveMatrix;
glm::mat4 perspectiveMatrix;
glm::mat4 viewMatrix;
//Matrix4GLF viewMatrix;
glm::mat4 modelMatrix;
//Matrix4GLF modelMatrix;
glm::mat4 modelViewMatrix;
//Matrix4GLF modelViewMatrix;
glm::mat4 translationModelMatrix;
glm::mat4 rotationModelMatrix;

GLuint renderingProgram;

GLuint vertexArrayObject[NUMBER_OF_VERTEX_ARRAY_OBJECTS];
GLuint vertexBufferObject[NUMBER_OF_VERTEX_BUFFER_OBJECTS];

GLuint modelViewLocation;
GLuint projectionLocation;

Utils util = Utils();


void setupVertices()
{
	float vertexPositionsCube[108] =
    {
		-1.0F,  1.0F, -1.0F, -1.0F, -1.0F, -1.0F,  1.0F, -1.0F, -1.0F, // 1
		 1.0F, -1.0F, -1.0F,  1.0F,  1.0F, -1.0F, -1.0F,  1.0F, -1.0F, // 2
		 1.0F, -1.0F, -1.0F,  1.0F, -1.0F,  1.0F,  1.0F,  1.0F, -1.0F, // 3
		 1.0F, -1.0F,  1.0F,  1.0F,  1.0F,  1.0F,  1.0F,  1.0F, -1.0F, // 4
		 1.0F, -1.0F,  1.0F, -1.0F, -1.0F,  1.0F,  1.0F,  1.0F,  1.0F, // 5
		-1.0F, -1.0F,  1.0F, -1.0F,  1.0F,  1.0F,  1.0F,  1.0F,  1.0F, // 6
		-1.0F, -1.0F,  1.0F, -1.0F, -1.0F, -1.0F, -1.0F,  1.0F,  1.0F, // 7
		-1.0F, -1.0F, -1.0F, -1.0F,  1.0F, -1.0F, -1.0F,  1.0F,  1.0F, // 8
		-1.0F, -1.0F,  1.0F,  1.0F, -1.0F,  1.0F,  1.0F, -1.0F, -1.0F, // 9
		 1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F,  1.0F, // 10
		-1.0F,  1.0F, -1.0F,  1.0F,  1.0F, -1.0F,  1.0F,  1.0F,  1.0F, // 11
		 1.0F,  1.0F,  1.0F, -1.0F,  1.0F,  1.0F, -1.0F,  1.0F, -1.0F  // 12
	};

    glGenVertexArrays(NUMBER_OF_VERTEX_ARRAY_OBJECTS, vertexArrayObject); // extracted
	glBindVertexArray(vertexArrayObject[0]); //
    glGenBuffers(NUMBER_OF_VERTEX_BUFFER_OBJECTS, vertexBufferObject); //

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[0]); //
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositionsCube), vertexPositionsCube, GL_STATIC_DRAW); //
}

void init(GLFWwindow* window) {
	renderingProgram = Utils::createShaderProgram("vertShader.glsl", "fragShader.glsl");
    cameraX = 0.0F;
    cameraY = 0.0F;
    cameraZ = 8.0F;
    cubeLocationX = 0.0F;
    cubeLocationY = -2.0F;
    cubeLocationZ = 0.0F;
    setupVertices();
}

void display(GLFWwindow* window, double currentTime)
{

	glClear(GL_DEPTH_BUFFER_BIT);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glUseProgram(renderingProgram); // extracted

    modelViewLocation = glGetUniformLocation(renderingProgram, "mv_matrix"); // Returns the location of a uniform variable // extracted
    projectionLocation = glGetUniformLocation(renderingProgram, "proj_matrix"); // extracted

    glfwGetFramebufferSize(window, &width, &height);
    aspect = static_cast<float>(width / height);
    
    perspectiveMatrix = glm::perspective(1.0472F, aspect, 0.1F, 1000.0F); // 1.0472 radians = 60 degrees
    //std::cout << (int)&perspectiveMatrix << std::endl;
    viewMatrix = glm::translate(glm::mat4(1.0F), glm::vec3(-cameraX, -cameraY, -cameraZ));
    
    // modelMatrix = glm::translate(glm::mat4(1.0F), glm::vec3(cubeLocationX, cubeLocationY, cubeLocationZ));
    
    translationModelMatrix = glm::translate(glm::mat4(1.0F), glm::vec3(sin(0.35F*currentTime)*2.0F, cos(0.52F*currentTime)*2.0F, sin(0.7F*currentTime)*2.0F));
    // 04.11.2020 translationModelMatrix = glm::translate(glm::mat4(1.0F), glm::vec3(1.0F, 1.0F, 1.0F));
    
    //rotationModelMatrix = glm::rotate(glm::mat4(1.0F), 1.75F*static_cast<float>(currentTime), glm::vec3(0.0F, 1.0F, 0.0F));
    //rotationModelMatrix = glm::rotate(rotationModelMatrix, 1.75F*static_cast<float>(currentTime), glm::vec3(1.0F, 0.0F, 0.0F));
    
    ///rotationModelMatrix = glm::rotate(glm::mat4(1.0F), 1.75F*static_cast<float>(currentTime), glm::vec3(0.0F, 0.0F, 1.0F));

    
//rotationModelMatrix = glm::rotate(glm::mat4(1.0F), 1.75F*static_cast<float>(currentTime), glm::vec3(0.0F, 1.0F, 0.0F));
//rotationModelMatrix = glm::rotate(rotationModelMatrix, 1.75F*static_cast<float>(currentTime), glm::vec3(1.0F, 0.0F, 0.0F));
//rotationModelMatrix = glm::rotate(rotationModelMatrix, 1.75F*static_cast<float>(currentTime), glm::vec3(0.0F, 0.0F, 1.0F));

    rotationModelMatrix = glm::rotate(glm::mat4(1.0F), 1.75F*static_cast<float>(currentTime), glm::vec3(1.0F, 0.0F, 0.0F));
    rotationModelMatrix = glm::rotate(rotationModelMatrix, 1.75F*static_cast<float>(currentTime), glm::vec3(0.0F, 1.0F, 0.0F));
    rotationModelMatrix = glm::rotate(rotationModelMatrix, 1.75F*static_cast<float>(currentTime), glm::vec3(0.0F, 0.0F, 1.0F));

   	//rMat = glm::rotate(rotationModelMatrix, 1.75f*(float)currentTime, glm::vec3(1.0f, 0.0f, 0.0f));
	//rMat = glm::rotate(rMat, 1.75f*(float)currentTime, glm::vec3(0.0f, 0.0f, 1.0f));

    modelMatrix = translationModelMatrix * rotationModelMatrix;

    modelViewMatrix = viewMatrix * modelMatrix;
    //modelViewMatrix = multiplyAbyB(viewMatrix, modelMatrix);

    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    //glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &(modelViewMatrix.x1)); // 
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(perspectiveMatrix)); //

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[0]); //
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0); //
    glEnableVertexAttribArray(0); //
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main()
{
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "For god sake regular hexahedron ", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }

	//glfwSwapInterval(1);

	init(window);

	while (!glfwWindowShouldClose(window)) {
		display(window, glfwGetTime());
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}