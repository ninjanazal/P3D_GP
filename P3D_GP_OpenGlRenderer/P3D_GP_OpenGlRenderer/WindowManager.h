// gestor de janelas e comportamento
#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H
// sao incluidas e definidas todas as librarias externas visto que todo o programa dependerá 
// maioritariamente, occorendo aqui grande parte da transformaçao do mesmo
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib")

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr
#include <iostream>
#include <string>


// classe que comporta o comportamento e gestao de janelas
namespace P3D
{
	class WindowManager
	{
	public:
		// metodos publicos
		// construtor do gestor de janelas	
		WindowManager(const char* name, unsigned int width, unsigned int height);
		~WindowManager() {};	// destrutor

		// funçoes da class
		// funçao para iniciaçao de uma nova janela
		bool CreateWindow();

#pragma region Getters
		// getter para a janela
		GLFWwindow* GetWindow(void) { return this->render_window; };
		// getter para matriz de projecçao
		glm::mat4 GetProjectionMat(void) { return this->projection_matrix; };
		// getter para a matriz de vista
		glm::mat4 GetViewMat(void) { return this->view_matrix; };
#pragma endregion

	private:
		// variaveis relativas á class
#pragma region InternalVars
		// internal vars
		std::string window_name;	// nome da janela
		unsigned int window_width, window_height;	// tamanho da janela de vista

		// GLF vars
		GLFWwindow* render_window;	// referencia da janela

		// render Vars
		glm::mat4 projection_matrix;	// matriz de projecçao
		glm::mat4 view_matrix;	// matriz de vista
#pragma endregion

		// variaveis que resultam no input do utilizador
#pragma region InputVars
		// input vars
		GLfloat mouse_zoom = 5.0f;	// zoom aplicado pelo scroll do rato
#pragma endregion

#pragma region Methods
		// funçoes de callback de comportamento da janela
#pragma endregion
	};

}
#endif