#include<iostream>
#include<string>
#include<iostream>
#include<fstream>
#include<Windows.h>
#include<gl/gl.h>
#include<glext.h>
#include<wglext.h>
//#include<GL\glew.h>
//#include<GLFW\glfw3.h>
//#include<glm\glm.hpp>
//#include<glm\gtc\type_ptr.hpp> // glm::value_ptr
//#include<glm\gtc\matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective
#include"Utils.h"
#include"YasMathsLib.hpp"

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

Matrix4GLF perspectiveMatrix;
//glm::mat4 perspectiveMatrix;
//glm::mat4 viewMatrix;
Matrix4GLF viewMatrix;
//glm::mat4 modelMatrix;
Matrix4GLF modelMatrix;
//glm::mat4 modelViewMatrix;
Matrix4GLF modelViewMatrix;

GLuint renderingProgram;

GLuint vertexArrayObject[NUMBER_OF_VERTEX_ARRAY_OBJECTS];
GLuint vertexBufferObject[NUMBER_OF_VERTEX_BUFFER_OBJECTS];

GLuint modelViewLocation;
GLuint projectionLocation;

Utils util = Utils();

        // OpenGL and extension function pointers:

        // For working with shaders
        PFNGLCREATESHADERPROC glCreateShader;
        PFNGLCREATEPROGRAMPROC glCreateProgram;
        PFNGLSHADERSOURCEPROC glShaderSource;
        PFNGLCOMPILESHADERPROC glCompileShader;
        PFNGLATTACHSHADERPROC glAttachShader;
        PFNGLLINKPROGRAMPROC glLinkProgram;
        PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
        PFNGLBINDVERTEXARRAYPROC glBindVertexArray;


        // For error checking and logging
        PFNGLGETSHADERIVPROC glGetShaderiv;
        PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
        PFNGLGETPROGRAMIVPROC glGetProgramiv;
        PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;

        // For rendering
        PFNGLUSEPROGRAMPROC glUseProgram;
        PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
        PFNGLPROGRAMUNIFORM1FEXTPROC glProgramUniform1f;

        // NEW ONES
        ////////////////
        PFNGLGENBUFFERSPROC glGenBuffers;
        PFNGLBINDBUFFERPROC glBindBuffer;
        PFNGLBUFFERDATAPROC glBufferData;
        PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
        PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
        PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;

void extractFunctionsPointers()
{
    // For working with shaders
    glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(wglGetProcAddress("glCreateShader"));
    glCreateProgram = reinterpret_cast<PFNGLCREATEPROGRAMPROC>(wglGetProcAddress("glCreateProgram"));
    glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(wglGetProcAddress("glShaderSource"));
    glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(wglGetProcAddress("glCompileShader"));
    glAttachShader = reinterpret_cast<PFNGLATTACHSHADERPROC>(wglGetProcAddress("glAttachShader"));
    glLinkProgram = reinterpret_cast<PFNGLLINKPROGRAMPROC>(wglGetProcAddress("glLinkProgram"));
    glGenVertexArrays = reinterpret_cast<PFNGLGENVERTEXARRAYSPROC>(wglGetProcAddress("glGenVertexArrays"));
    glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));
    
    // For error checking and logging
    glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(wglGetProcAddress("glGetShaderiv"));
    glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(wglGetProcAddress("glGetShaderInfoLog"));
    glGetProgramiv = reinterpret_cast<PFNGLGETPROGRAMIVPROC>(wglGetProcAddress("glGetProgramiv"));
    glGetProgramInfoLog = reinterpret_cast<PFNGLGETPROGRAMINFOLOGPROC>(wglGetProcAddress("glGetProgramInfoLog"));

    // For rendering
    glUseProgram = reinterpret_cast<PFNGLUSEPROGRAMPROC>(wglGetProcAddress("glUseProgram"));
    glGetUniformLocation = reinterpret_cast<PFNGLGETUNIFORMLOCATIONPROC>(wglGetProcAddress("glGetUniformLocation"));
    glProgramUniform1f = reinterpret_cast<PFNGLPROGRAMUNIFORM1FEXTPROC>(wglGetProcAddress("glProgramUniform1f"));

    // New ones
    //glBindVertexArray = reinterpret_cast<PFNGLBINDVERTEXARRAYPROC>(wglGetProcAddress("glBindVertexArray"));

    glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(wglGetProcAddress("glGenBuffers"));

    glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(wglGetProcAddress("glBindBuffer"));

    glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(wglGetProcAddress("glBufferData"));

    glUniformMatrix4fv = reinterpret_cast<PFNGLUNIFORMMATRIX4FVPROC>(wglGetProcAddress("glUniformMatrix4fv"));

    glVertexAttribPointer = reinterpret_cast<PFNGLVERTEXATTRIBPOINTERPROC>(wglGetProcAddress("glVertexAttribPointer"));

    glEnableVertexAttribArray = reinterpret_cast<PFNGLENABLEVERTEXATTRIBARRAYPROC>(wglGetProcAddress("glEnableVertexAttribArray"));
    // End new ones
}



void setupVertices()
{
	float vertexPositionsCube[108] =
    {
		-1.0F,  1.0F, -1.0F, -1.0F, -1.0F, -1.0F,  1.0F, -1.0F, -1.0F,
		 1.0F, -1.0F, -1.0F,  1.0F,  1.0F, -1.0F, -1.0F,  1.0F, -1.0F,
		 1.0F, -1.0F, -1.0F,  1.0F, -1.0F,  1.0F,  1.0F,  1.0F, -1.0F,
		 1.0F, -1.0F,  1.0F,  1.0F,  1.0F,  1.0F,  1.0F,  1.0F, -1.0F,
		 1.0F, -1.0F,  1.0F, -1.0F, -1.0F,  1.0F,  1.0F,  1.0F,  1.0F,
		-1.0F, -1.0F,  1.0F, -1.0F,  1.0F,  1.0F,  1.0F,  1.0F,  1.0F,
		-1.0F, -1.0F,  1.0F, -1.0F, -1.0F, -1.0F, -1.0F,  1.0F,  1.0F,
		-1.0F, -1.0F, -1.0F, -1.0F,  1.0F, -1.0F, -1.0F,  1.0F,  1.0F,
		-1.0F, -1.0F,  1.0F,  1.0F, -1.0F,  1.0F,  1.0F, -1.0F, -1.0F,
		 1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F, -1.0F,  1.0F,
		-1.0F,  1.0F, -1.0F,  1.0F,  1.0F, -1.0F,  1.0F,  1.0F,  1.0F,
		 1.0F,  1.0F,  1.0F, -1.0F,  1.0F,  1.0F, -1.0F,  1.0F, -1.0F
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

void display(GLFWwindow* window, double currentTime) {
	glClear(GL_DEPTH_BUFFER_BIT);
    
    glUseProgram(renderingProgram); // extracted

    modelViewLocation = glGetUniformLocation(renderingProgram, "mv_matrix"); // Returns the location of a uniform variable // extracted
    projectionLocation = glGetUniformLocation(renderingProgram, "proj_matrix"); // extracted

    glfwGetFramebufferSize(window, &width, &height);
    aspect = static_cast<float>(width / height);
    
    //perspectiveMatrix = glm::perspective(1.0472F, aspect, 0.1F, 1000.0F); // 1.0472 radians = 60 degrees
    //perspectiveMatrix = glm::perspective(1.0472F, aspect, 0.1F, 1000.0F); // 1.0472 radians = 60 degrees
    //static Matrix4F buildPerspectiveProjectionMatrix(float fieldOfViewY, float aspectRatio, float zNearPlane, float zFarPlane)
    perspectiveMatrix = buildPerspectiveProjectionMatrixGLF(1.0472F, aspect, 0.1F, 1000.0F);


    //viewMatrix = glm::translate(glm::mat4(1.0F), glm::vec3(-cameraX, -cameraY, -cameraZ));
    viewMatrix = buildTranslationMatrixGL(-cameraX, -cameraY, -cameraZ);
    //modelMatrix = glm::translate(glm::mat4(1.0F), glm::vec3(cubeLocationX, cubeLocationY, cubeLocationZ));
    modelMatrix = buildTranslationMatrixGL(cubeLocationX, cubeLocationY, cubeLocationZ);
    
    //modelViewMatrix = viewMatrix * modelMatrix;
    modelViewMatrix = multiplyAbyB(viewMatrix, modelMatrix);

    //glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, glm::value_ptr(modelViewMatrix));
    glUniformMatrix4fv(modelViewLocation, 1, GL_FALSE, &(modelViewMatrix.x1)); // 
    glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, &(perspectiveMatrix.x1)); //

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject[0]); //
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0); //
    glEnableVertexAttribArray(0); //
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glDrawArrays(GL_TRIANGLES, 0, 36);
}

int main() {
	if (!glfwInit()) { exit(EXIT_FAILURE); }
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	GLFWwindow* window = glfwCreateWindow(600, 600, "For god sake regular hexahedron ", NULL, NULL);
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK) { exit(EXIT_FAILURE); }

	glfwSwapInterval(1);

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