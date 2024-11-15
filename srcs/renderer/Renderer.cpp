#include "Renderer.hpp"
#include "Camera.hpp"
#include "ShaderManager.hpp"
#include "object/Object.hpp"
#include <GLFW/glfw3.h>
#include <glm/ext/vector_uint3.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Camera	   *Renderer::_globalCamera = NULL;
GLFWwindow *Renderer::_window = NULL;
float	    Renderer::_lastX = SCREEN_WIDTH / 2.0f;
float	    Renderer::_lastY = SCREEN_HEIGHT / 2.0f;
bool	    Renderer::_firstMouse = true;

// timing
float Renderer::_deltaTime = 0.0f; // time between current frame and last frame
float Renderer::_lastFrame = 0.0f;

void Renderer::framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	(void)window;
	// make sure the viewport matches the new _window dimensions; note that width and
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

void Renderer::processInput(GLFWwindow *window)
{
	(void)window;
	if(glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);

	if(glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
		_globalCamera->ProcessKeyboard(FORWARD, _deltaTime);
	if(glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
		_globalCamera->ProcessKeyboard(BACKWARD, _deltaTime);
	if(glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
		_globalCamera->ProcessKeyboard(LEFT, _deltaTime);
	if(glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
		_globalCamera->ProcessKeyboard(RIGHT, _deltaTime);
	if(glfwGetKey(_window, GLFW_KEY_SPACE) == GLFW_PRESS)
		_globalCamera->ProcessKeyboard(UP, _deltaTime);
	if(glfwGetKey(_window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		_globalCamera->ProcessKeyboard(DOWN, _deltaTime);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void Renderer::mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
	(void)window;
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if(_firstMouse)
	{
		_lastX = xpos;
		_lastY = ypos;
		_firstMouse = false;
	}

	float xoffset = xpos - _lastX;
	float yoffset = _lastY - ypos; // reversed since y-coordinates go from bottom to top

	_lastX = xpos;
	_lastY = ypos;

	_globalCamera->ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void Renderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
	(void)window;
	(void)xoffset;
	_globalCamera->ProcessMouseScroll(static_cast<float>(yoffset));
}
Renderer::Renderer()
{

	/* Initialize the library */
	if(!glfwInit())
		return;

	/* Create a _windowed mode _window and its OpenGL context */
	Renderer::_window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "planet", NULL, NULL);
	if(!_window)
	{
		glfwTerminate();
		return;
	}

	/* Make the _window's context current */
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}
	glEnable(GL_DEPTH_TEST);
}

Renderer::~Renderer() {}

void Renderer::setCamera(Scene &scene)
{
	Camera *camera = scene.getCamera();

	_globalCamera = camera;
	glfwSetCursorPosCallback(_window, mouse_callback);
	glfwSetScrollCallback(_window, scroll_callback);
}

void Renderer::render(Scene &scene)
{
	processInput(_window);
	glClearColor(0.13f, 0.13f, 0.13f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float currentFrame = static_cast<float>(glfwGetTime());
	Renderer::_deltaTime = currentFrame - Renderer::_lastFrame;
	Renderer::_lastFrame = currentFrame;
	std::vector<Object> objects = scene.getObjects();

	for(auto obj : objects)
	{
		ShaderManager shaderManager = obj.getShaderManager();

		glBindVertexArray(obj.getVao());
		/* Render here */
		glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
		glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 model = glm::mat4(1.0f);

		projection = glm::perspective(glm::radians(_globalCamera->Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 10000.0f);
		view = _globalCamera->GetViewMatrix();
		model = glm::translate(model, obj.getPosition());

		shaderManager.useShader();
		shaderManager.setMat4("projection", projection);
		shaderManager.setMat4("view", view);
		shaderManager.setMat4("model", model);
		shaderManager.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
		// TODO: Group all scene light under one vector and apply them one all render that are not themselves
		shaderManager.setVec3("lightPos", 0.0f, 20.0f, 0.0f);

		// glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, obj.getIndices().size() * 3, GL_UNSIGNED_INT, 0);
	}
	glfwSwapBuffers(_window);
	glfwPollEvents();
}

bool Renderer::shouldClose() { return glfwWindowShouldClose(_window); }
