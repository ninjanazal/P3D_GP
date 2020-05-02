#pragma once
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")


#define GLEW_STATIC
#include <GL\glew.h>

#include <GLFW\glfw3.h>

namespace P3D
{
	// Funçao de iniciaçao para o estado do GL
	bool InitGLFW(void);
	// Funçao de fecho do GLFW
	void CloseGL(void);
	// Funçao de iniciaçao de glew
	bool InitGLEW(void);
	// Funçao de impressao das informaçoes de OpenGl
	void PrintGlInformation(void);
	// Funçao de iniciaçao de valores de OpenGl
	void InitOpenGL(void);
}
