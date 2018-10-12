#pragma once

#include "shapes.h"



void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void key_button_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void drawShapes();
//void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
vec2 screenToWorld(GLFWwindow *w,vec2);


class Init
{		

public :
	const unsigned int SCR_WIDTH = 600;
	const unsigned int SCR_HEIGHT = 600;

	GLFWwindow* window;
	GLuint ShaderProg;
	
	Init() {

		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		// glfw window creation
		// --------------------
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);



		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;

			glfwTerminate();
			exit(0);
		}
		glfwMakeContextCurrent(window);
		
		// glad: load all OpenGL function pointers
		// ---------------------------------------
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			exit(0);
		}


		Shader s;
		ShaderProg = s.InitShader("vshader21.glsl", "fshader21.glsl");
	}

	

};