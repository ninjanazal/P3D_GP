#pragma once
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "opengl32.lib")


#define GLEW_STATIC
#include <GL\glew.h>

#include <GLFW\glfw3.h>

namespace P3D
{
	// Fun�ao de inicia�ao para o estado do GL
	bool InitGLFW(void);
	// Fun�ao de fecho do GLFW
	void CloseGL(void);
	// Fun�ao de inicia�ao de glew
	bool InitGLEW(void);
	// Fun�ao de impressao das informa�oes de OpenGl
	void PrintGlInformation(void);
	// Fun�ao de inicia�ao de valores de OpenGl
	void InitOpenGL(void);
}
