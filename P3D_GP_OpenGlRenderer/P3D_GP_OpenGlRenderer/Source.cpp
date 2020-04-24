// Trabalho pr�tico - Programa�ao 3D
// renderer 3D para obj's
/*
Fase 1[5 valores]:
� Implementar a gest�o de janelas e interface com o utilizador atrav�s da biblioteca GLFW;
� Implementar a manipula��o de matrizes e vetores atrav�s da biblioteca GLM;
�(2) Implementar a renderiza��o de um cubo atrav�s da biblioteca OpenGL(incluindo a GLEW);
�(2) A colora��o dos fragmentos do cubo deve ser realizada de modo a que cada face apresente uma cor
	distinta(nota que n�o � esperado que nesta fase estejam implementados os efeitos de ilumina��o);
� A aplica��o dever� permitir ao utilizador realizar zoom atrav�s da scroll wheel do rato;
� A aplica��o dever� permitir navegar, em torno do modelo 3D, atrav�s de movimentos do rato.
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
	// defini��o de objectos
	Object* obj_to_render_;	// define um novo objecto
	WindowManager* window_manager_;	// controlador de janelas

#pragma endregion Vars

	// define vertices de inicia��o do cubo
	glm::vec3 point_[6 * 4] = {
		// Frente
		glm::vec3(-1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f, -1.0f,  1.0f),
		glm::vec3(1.0f,  1.0f,  1.0f),
		glm::vec3(-1.0f,  1.0f,  1.0f),
		// Tr�s
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

	// define o novo cubo, para combeniencia � passado aqui o numero de vertices a criar
	obj_to_render_ = new Object(point_, sizeof(point_) / sizeof(point_[0]));	// inicia o novo objecto


	// aguarda o input
	std::cin.get();
	return 0;
}