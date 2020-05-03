#pragma once
#include "WindowManager.h"

// namespace P3D para comportamentos singulares
namespace P3D
{
	// Funçao de iniciaçao para o estado do GL
	bool InitGLFW();
	// Funçao de fecho do GLFW
	void CloseGL(void);
	// Funçao de iniciaçao de glew
	bool InitGLEW(void);
	// Funçao de impressao das informaçoes de OpenGl
	void PrintGlInformation(void);
	// Funçao de iniciaçao de valores de OpenGl
	void InitOpenGL(void);

	// Funçao de preparaçao do estado do GL
	bool StartStateGl(P3D::WindowManager& manager);
}