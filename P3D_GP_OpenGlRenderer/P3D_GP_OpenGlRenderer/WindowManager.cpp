#include "WindowManager.h"

namespace P3D {

	// inicalizador do gestor de janelas
	WindowManager::WindowManager(const char* window_name, unsigned int width, unsigned int height) :
		window_name(window_name), window_width(width), window_height(height) {
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
			camera_center - (glm::normalize(camera_relative_direction) * mouse_zoom),	// eye (posição da câmara).
			camera_center,						// center
			glm::vec3(0.0f, 1.0f, 0.0f)			// up
		);

		// se conseguiu criar a janela
		// informa
		std::cout << "Window created successfully!\n-> " << window_width << " : " << window_height << std::endl;
		// retorna
		return true;
	}
#pragma region runTimeCallBacks
	// handler para o callback de scroll
	void WindowManager::ScrollInputHandler(double yoffset)
	{
		// o scrool do rato influencia a distancia, define o zoom
		this->mouse_zoom -= SCROLL_SPEED * yoffset;

		// actualiza a matriz de vista
		this->view_matrix = glm::lookAt(
			camera_center - (glm::normalize(camera_relative_direction) * mouse_zoom),	// eye (posição da câmara).
			camera_center,		// center
			glm::vec3(0.0f, 1.0f, 0.0f));
	}
	// Metodo que roda camera em torno do seu foco
	void WindowManager::RotateCameraAroundHandler(float xValue, float yValue) {
		// adiciona ao valor do angulo actual
		this->camera_yaw_angle += xValue * ROTATION_SPEED;
		// impede que a camera rode para lá de valores pretendidos
		if (camera_pitch_angle - (yValue * ROTATION_SPEED ) < 85.0f && camera_pitch_angle - (yValue * ROTATION_SPEED) > -85.0f)
			this->camera_pitch_angle -= yValue * ROTATION_SPEED;

		//// define o vector de direcçao relativo 	
		camera_relative_direction.x = glm::cos(glm::radians(camera_yaw_angle)) * glm::cos(glm::radians(camera_pitch_angle));
		camera_relative_direction.y = glm::sin(glm::radians(camera_pitch_angle));
		camera_relative_direction.z = glm::sin(glm::radians(camera_yaw_angle)) * glm::cos(glm::radians(camera_pitch_angle));

		// actualiza a matriz de vista
		this->view_matrix = glm::lookAt(
			camera_center - (glm::normalize(camera_relative_direction) * mouse_zoom),	// eye (posição da câmara).
			camera_center,		// center
			glm::vec3(0.0f, 1.0f, 0.0f));
	}
#pragma endregion
}