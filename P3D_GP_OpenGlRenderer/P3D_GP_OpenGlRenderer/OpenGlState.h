#pragma once
#include "WindowManager.h"
#include "Object.h"
#include "Light.h"

// namespace P3D para comportamentos singulares
namespace P3D
{
	// inicia luzes 
	void InitLights(P3D::Light*lights);

	// Fun�ao de inicia�ao para o estado do GL
	bool InitGLFW();
	// Fun�ao de fecho do GLFW
	void CloseGL(void);
	// Fun�ao de inicia�ao de glew
	bool InitGLEW(void);
	// Fun�ao de impressao das informa�oes de OpenGl
	void PrintGlInformation(void);
	// Fun�ao de inicia�ao de valores de OpenGl
	void InitOpenGL(void);

	// Fun�ao de prepara�ao do estado do GL
	bool StartStateGl(P3D::WindowManager& manager);

	// Fun�ao de atribui�ao de valores uniformes
	void ConnectUniformValues(P3D::WindowManager* manager, P3D::Object* obj, P3D::Light* lights);
	// Fun�ao de render do estado do GL
	void DrawGL(P3D::WindowManager* manager, P3D::Object* obj, P3D::Light* lights);
}