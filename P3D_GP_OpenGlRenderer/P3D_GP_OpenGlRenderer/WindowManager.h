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

#define SCROLL_SPEED 0.5
#define ROTATION_SPEED 1

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

#pragma region CallBackHandlers
		// define os handler para InputCallbacks
		// scrool de rato (Handler)
		void ScrollInputHandler(double yoffset);
		// input do rato
		// roda a camera em torno do alvo(Handler)
		void RotateCameraAroundHandler(float xValue, float yvalue);
#pragma endregion -> CallBackHandlers


#pragma region Getters
		// getter para a janela
		GLFWwindow* GetWindow(void) { return this->render_window; };
		// getter para matriz de projecçao
		glm::mat4 GetProjectionMat(void) { return this->projection_matrix; };
		// getter para a matriz de vista
		glm::mat4 GetViewMat(void) { return this->view_matrix; };
#pragma endregion -> Getters


	private:
		// variaveis relativas á class
#pragma region InternalVars
		// internal vars
		std::string window_name;	// nome da janela
		unsigned int window_width, window_height;	// tamanho da janela de vista

		// GLF vars
		GLFWwindow* render_window;	// referencia da janela

		// render Vars
		glm::mat4 projection_matrix = glm::mat4(1.0f);	// matriz de projecçao
		glm::mat4 view_matrix = glm::mat4(1.0f);	// matriz de vista
#pragma endregion -> InternalVars

		// variaveis que resultam no input do utilizador
#pragma region InputVars
		// input vars
		GLfloat mouse_zoom = 5.0f;	// zoom aplicado pelo scroll do rato
		GLfloat camera_pitch_angle = 0.0f, camera_yaw_angle = -90.0f;	// valor de rotaçao dos angulos de pitch e yaw
		glm::vec3 camera_relative_direction = glm::vec3(0.0f,0.0f,-1.0f);	// direcçao da camera relativa ao centro
		glm::vec3 camera_center = glm::vec3(0.0f, 2.0f, 0.0f);			// posiçao de foco da camera, centro
#pragma endregion -> InputVars
	};
}
#endif