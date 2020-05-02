// gestor de janelas e comportamento
#pragma once
#include "Object.h"
#include "CallBacksDeff.h"

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
	};

	// inicalizador do gestor de janelas
	WindowManager::WindowManager(const char* window_name, unsigned int width, unsigned int height)
	{
		// guarda internamente os valores passados
		this->window_name = window_name;	// guarda o nome a apresentar na janela
		this->window_width = width;			// guarda a largura e altura da janela
		this->window_height = height;
		// informa da criaçao da janela
		std::cout << "Ready To create Window: " << this->window_name << std::endl;
	}

	// cria uma nova janela
	bool WindowManager::CreateWindow(void)
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
}
