// gestor de janelas e comportamento
#pragma once
#include "Object.h"

// classe que comporta o comportamento e gestao de janelas
namespace P3D
{
	class WindowManager
	{
	public:
		// construtor
		WindowManager(const char*);
		// destrutor
		~WindowManager() { std::cout << "Object material destroid" << std::endl; };	// destrutor do material

	private:
		GLfloat mouse_zoom = 10.0f;	// zoom aplicado pelo scroll do rato
	};
	// construtor do objecto, recebe o caminho para ler o material
	WindowManager::WindowManager(const char* path)
	{

	}
}
