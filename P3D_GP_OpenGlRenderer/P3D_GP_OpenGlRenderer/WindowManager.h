// gestor de janelas e comportamento
#pragma once
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

// classe que comporta o comportamento e gestao de janelas
namespace P3D
{
	class WindowManager
	{
	public:
		WindowManager();
		~WindowManager();

	private:
		GLfloat mouse_zoom = 10.0f;	// zoom aplicado pelo scroll do rato
	};

	WindowManager::WindowManager()
	{
	}

	WindowManager::~WindowManager()
	{
	}
}
