#include "WindowManager.h"

namespace P3D {

	// inicalizador do gestor de janelas
	WindowManager::WindowManager(const char* window_name, unsigned int width, unsigned int height) {
		// guarda internamente os valores passados
		this->window_name = window_name;	// guarda o nome a apresentar na janela
		this->window_width = width;			// guarda a largura e altura da janela
		this->window_height = height;
		// informa da criaçao da janela
		std::cout << "Ready To create Window: " << this->window_name << std::endl;
	}
	// cria uma nova janela
	bool WindowManager::CreateWindow(void) {
		// define uma nova janela
		render_window = glfwCreateWindow(
			this->window_width, this->window_height, this->window_name.c_str(), NULL, NULL);

		// verifica se foi criada com sucesso
		if (render_window == NULL) {
			// inprime que nao conseguiu criar a janela
			std::cout << "Failed to create window: " << this->window_name << std::endl;
			// retorna
			return false;
		}

		// define a matriz de projecçao, fov 60º, near plane 0.1, far plane 500f
		this->projection_matrix = glm::perspective(glm::radians(60.0f),
			(float)window_width / (float)window_height, 0.1f, 500.0f);

		//define a matriz de vista inicial
		this->view_matrix = glm::lookAt(
			glm::vec3(0.0f, 2.0f, mouse_zoom),	// eye (posição da câmara).
			glm::vec3(0.0f, 2.0f, 0.0f),		// center
			glm::vec3(0.0f, 1.0f, 0.0f)			// up
		);

		// se conseguiu criar a janela
		// informa
		std::cout << "Window created successfully!\n-> " << window_width << " : " << window_height << std::endl;
		// retorna
		return true;
	}


#pragma region runTimeCallBacks

#pragma endregion
}