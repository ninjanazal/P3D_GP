#pragma once
#include "WindowManager.h"
#include "Object.h"
#include "Light.h"

// namespace P3D para comportamentos singulares
namespace P3D
{
	// inicia luzes 
	void InitLights(P3D::Light*lights);

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

	// Funçao de atribuiçao de valores uniformes
	void ConnectUniformValues(P3D::WindowManager* manager, P3D::Object* obj, P3D::Light* lights);
	// Funçao de render do estado do GL
	void DrawGL(P3D::WindowManager* manager, P3D::Object* obj, P3D::Light* lights);
}