// Trabalho prático - Programaçao 3D
// renderer 3D para obj's
/*
Fase 1[5 valores]:
• Implementar a gestão de janelas e interface com o utilizador através da biblioteca GLFW;
• Implementar a manipulação de matrizes e vetores através da biblioteca GLM;
•(2) Implementar a renderização de um cubo através da biblioteca OpenGL(incluindo a GLEW);
•(2) A coloração dos fragmentos do cubo deve ser realizada de modo a que cada face apresente uma cor
	distinta(nota que não é esperado que nesta fase estejam implementados os efeitos de iluminação);
• A aplicação deverá permitir ao utilizador realizar zoom através da scroll wheel do rato;
• A aplicação deverá permitir navegar, em torno do modelo 3D, através de movimentos do rato.
*/

// includes
#include "Object.h"
#include "Windowmanager.h"


int main(void)
{
	using namespace P3D;	// utilizando o nameSpace
	// debugging
	std::cout << " ***** Starting *****\n";
	
#pragma region Vars
	// definição de objectos
	Object* obj_to_render_;	// define um novo objecto
	WindowManager* window_manager_;	// controlador de janelas

#pragma endregion Vars

	// define vertices de iniciação do cubo
	glm::vec3 point_[6 * 4] = {
		// Frente
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		// Trás
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		// Direita
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		// Esquerda
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		// Cima
		glm::vec3(-1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f, -1.0f),
		glm::vec3(-1.0f,  1.0f, -1.0f),
		// Baixo
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f, -1.0f),
		glm::vec3(-1.0f, -1.0f, -1.0f)
	};

	// define o novo cubo, para combeniencia é passado aqui o numero de vertices a criar
	obj_to_render_ = new Object(point_, sizeof(point_) / sizeof(point_[0]));	// inicia o novo objecto


	// aguarda o input
	std::cin.get();
	return 0;
}