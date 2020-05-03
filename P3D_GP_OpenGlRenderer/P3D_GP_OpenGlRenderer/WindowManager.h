// gestor de janelas e comportamento
#pragma once
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
		inline WindowManager(const char* name, unsigned int width, unsigned int height);
		~WindowManager() {};	// destrutor

		// funçoes da class
		// funçao para iniciaçao de uma nova janela
		inline bool CreateWindow();

#pragma region Getters
		// getter para a janela
		inline GLFWwindow* GetWindow(void) { return this->render_window; };
#pragma endregion

	private:
		// variaveis relativas á class
#pragma region InternalVars
		// internal vars
		std::string window_name;	// nome da janela
		unsigned int window_width, window_height;	// tamanho da janela de vista

		// GLF vars
		GLFWwindow* render_window;	// referencia da janela
#pragma endregion


		// variaveis que resultam no input do utilizador
#pragma region InputVars
		// input vars
		GLfloat mouse_zoom = 10.0f;	// zoom aplicado pelo scroll do rato
		glm::vec2 mouse_input = glm::vec2(0.0f, 0.0f);
#pragma endregion

#pragma region Methods
		// funçoes de callback de comportamento da janela
#pragma endregion
	};

	// inicalizador do gestor de janelas
	inline WindowManager::WindowManager(const char* window_name, unsigned int width, unsigned int height)
	{
		// guarda internamente os valores passados
		this->window_name = window_name;	// guarda o nome a apresentar na janela
		this->window_width = width;			// guarda a largura e altura da janela
		this->window_height = height;
		// informa da criaçao da janela
		std::cout << "Ready To create Window: " << this->window_name << std::endl;
	}
	// cria uma nova janela
	inline bool WindowManager::CreateWindow(void)
	{
		// define uma nova janela
		render_window = glfwCreateWindow(
			this->window_width, this->window_height, this->window_name.c_str(), NULL, NULL);

		// verifica se foi criada com sucesso
		if (render_window == NULL)
		{
			// inprime que nao conseguiu criar a janela
			std::cout << "Failed to create window: " << this->window_name << std::endl;
			// retorna
			return false;
		}
		// se conseguiu criar a janela
		// informa
		std::cout << "Window created successfully!" << std::endl;
		// retorna
		return true;
	}


#pragma region runTimeCallBacks
	
#pragma endregion
}
