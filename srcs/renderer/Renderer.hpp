#pragma once

#include "scene/Scene.hpp"
#include <GLFW/glfw3.h>

#define SCREEN_HEIGHT 720
#define SCREEN_WIDTH 1080

class Renderer {
      private:
	static Camera	  *_globalCamera;
	static GLFWwindow *_window;

      public:
	Renderer();
	~Renderer();

	static float _lastX;
	static float _lastY;
	static bool  _firstMouse;

	// timing
	static float _deltaTime;
	static float _lastFrame;

	static void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
	static void mouse_callback(GLFWwindow *window, double xposIn, double yposIn);
	static void framebuffer_size_callback(GLFWwindow *window, int width, int height);
	static void processInput(GLFWwindow *window);

	bool shouldClose();

	void setCamera(Scene &scene);
	void render(Scene &scene);
};
