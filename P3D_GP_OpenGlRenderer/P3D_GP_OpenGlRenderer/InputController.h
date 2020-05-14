#pragma once
#include "Object.h"
#include "WindowManager.h"
#include "Light.h"

namespace P3D {

	class InputController {
	private:
		// vars
		P3D::WindowManager* window_manager_;	// referencia ao window manager
		P3D::Object* object_;		// referencia ao object
		P3D::Light* lights_;		// referencia para um array de luzes

		// variaveis de comportamento de input
		bool left_mouse_pressed = false;	// indica se o botao esquerdo está pressionado
		double last_mouse_position[2]{};	// ultima posiçao do rato

	public:
		InputController(P3D::WindowManager* manager, P3D::Object* obj, P3D::Light* lights);	// construtor da class
		~InputController() {};	// destrutor da class

		// Funçao para atribuir as funçoes de callbacks de input
		void SetCallbacksFuncs();

		// update para valores 
		void Update();

		// Metodo de callback para o scroll do rato
		void ScrollCallBack(GLFWwindow* window, double xoffset, double yoffset);
		// Metodo de callback para o press do rato
		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		// Metodo de callback para input do teclado
		void KeyboardInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}
