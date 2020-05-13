#pragma once
#include "InputController.h"

namespace P3D {

	InputController::InputController(P3D::WindowManager* manager, P3D::Object* obj) :
		window_manager_(manager), object_(obj) {
		// informa que o controlador de input está definido
		std::cout << "Input Controller setted!" << std::endl;
	}

	// funçao de call back para o scroll do rato
	void InputController::ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset) {
		// ao chamar indica ao gestor de janela atribuido os valores 
		this->window_manager_->ScrollInputHandler(yoffset);
	}

	// Funcçao de callback para press dos botoes do rato
	void InputController::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		// verifica se o botao esquerdo do rato foi pressionado
		if (button == GLFW_MOUSE_BUTTON_LEFT) {
			// verifica se o botao foi pressionado ou largado
			if (action == GLFW_PRESS) {
				// caso tenha sido pressionado, actualiza a variavel interna que indica que foi pressionado
				this->left_mouse_pressed = true;
				// define a ultima posiçao como a posiçao actual
				glfwGetCursorPos(window, &last_mouse_position[0], &last_mouse_position[1]);
			}
			else if (action == GLFW_RELEASE) {
				// caso tenha largado o botao, define o valor para false
				this->left_mouse_pressed = false;
			}
		}
	}
	// Metodo de callback para input do teclado
	void InputController::KeyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		// verifica a tecla pressionada
		if (key == GLFW_KEY_E && action == GLFW_PRESS) {
			// caso tenha pressionado no 'E' chama a funçao de handel da distorçao do obj
			this->object_->DeformationInputHandler();
		}
		// caso a tecla w esteja pressionada
		else if (key == GLFW_KEY_W && glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
			// invoca handler de resposta
			this->window_manager_->UpDownCameraTarget(1.0f);
		}
		else if (key == GLFW_KEY_S && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
			// invoca handler de resposta
			this->window_manager_->UpDownCameraTarget(-1.0f);
		}
	}

	// funçao para atribuir as funçoes de callbacks de input
	void InputController::SetCallbacksFuncs() {
		// para atribuir ao callback um metodo membro
		// define o apontador para a janela 
		glfwSetWindowUserPointer(this->window_manager_->GetWindow(), this);

		/* ======================= Scroll =====================*/
		// define a funçao
		auto this_callback_scroll = [](GLFWwindow* w, double x, double y) {
			static_cast<InputController*>(glfwGetWindowUserPointer(w))->ScrollCallBack(w, x, y); };
		// define o callback de acordo com a funçao determinada anteriormente 
		glfwSetScrollCallback(this->window_manager_->GetWindow(), this_callback_scroll);


		/* ======================= Input Mouse =====================*/
		// define a funçao
		auto this_callback_mouseInput = [](GLFWwindow* w, int b, int a, int m) {
			static_cast<InputController*>(glfwGetWindowUserPointer(w))->MouseButtonCallback(w, b, a, m); };
		// define o callback de acordo com a funçao determinada anteriormente
		glfwSetMouseButtonCallback(this->window_manager_->GetWindow(), this_callback_mouseInput);


		/* ======================= Input Keyboard =====================*/
		// define a funçao de callback
		auto this_callback_keyboardInput = [](GLFWwindow* w, int k, int sm, int a, int m) {
			static_cast<InputController*>(glfwGetWindowUserPointer(w))->KeyboardInputCallback(w, k, sm, a, m); };
		// define o callback de acordo com a fucçao determinada anteriormente
		glfwSetKeyCallback(this->window_manager_->GetWindow(), this_callback_keyboardInput);

		// informa que todos os callbacks foram atribuidos
		std::cout << "\n\n-> All Callbacs setted successfully!" << std::endl;
	}

	// metodo de update para actualizar dados
	void InputController::Update() {
		// verifica se o botao está pressionado
		if (left_mouse_pressed) {
			// caso esteja, deve chamar a funçao de rotaçao do objecto de acordo com o deslocamento do rato
			// no frame
			// variavel temporaria para guardar a posiçao actual
			double current_mouse_pos[2]{};
			// guarda a posiçao actual
			glfwGetCursorPos(this->window_manager_->GetWindow(), &current_mouse_pos[0], &current_mouse_pos[1]);

			// chama a funçao de rotaçao do objecto
			this->window_manager_->RotateCameraAroundHandler(current_mouse_pos[0] - last_mouse_position[0],
				current_mouse_pos[1] - last_mouse_position[1]);

			// define o ultima posiçao como a posiçao actual
			std::copy(std::begin(current_mouse_pos), std::end(current_mouse_pos), last_mouse_position);
		}
	}
}