// Trabalho pr�tico - Programa�ao 3D
// renderer 3D para obj's -> material -> texture (tga file)
//	using VAO e 

/*
Fase 1[5 valores]:
� Implementar a gest�o de janelas e interface com o utilizador atrav�s da biblioteca GLFW;
� Implementar a manipula��o de matrizes e vetores atrav�s da biblioteca GLM;
�(2) Implementar a renderiza��o de um cubo atrav�s da biblioteca OpenGL(incluindo a GLEW);
�(2) A colora��o dos fragmentos do cubo deve ser realizada de modo a que cada face apresente uma cor
	distinta(nota que n�o � esperado que nesta fase estejam implementados os efeitos de ilumina��o);
� A aplica��o dever� permitir ao utilizador realizar zoom atrav�s da scroll wheel do rato;
� A aplica��o dever� permitir navegar, em torno do modelo 3D, atrav�s de movimentos do rato.

Fase 2 [6 valores]:
� Os alunos dever�o desenvolver uma biblioteca C++ capaz de:
o Carregar os dados de posi��o dos v�rtices, normais, e coordenadas de textura do ficheiro .xyz;
o Enviar para a mem�ria de GPU (VAO e respetivos VBOs) os dados dos v�rtices;
o Identificar no ficheiro .xyz o nome do ficheiro .mtl;
o Carregar as propriedades do material (ficheiro .mtl), incluindo a imagem de textura;
o Carregar a imagem de textura para uma unidade de textura do OpenGL;
o Disponibilizar fun��o para renderiza��o do objeto.
� A aplica��o dever� fazer uso dessa biblioteca C++ para carregar e renderizar o modelo 3D fornecido;

- Fase 3 [6 valores]:
� Dever� ser poss�vel aplicar uma qualquer combina��o de 4 fontes de luz que incidam sobre o objeto:
o Luz ambiente;
o Luz direcional;
o Luz pontual;
o Luz c�nica.
� Os par�metros de cada uma das fontes de luz ficam ao crit�rio de cada grupo;
� A aplica��o dever� permitir ao utilizador ativar/desativar cada fonte de luz, atrav�s de uma tecla:
o �1� � Ativar/desativar fonte de luz ambiente;
o �2� � Ativar/desativar fonte de luz direcional;
o �3� � Ativar/desativar fonte de luz pontual;
o �4� � Ativar/desativar fonte de luz c�nica.

- Fase 4 [3 valores]:
� Dotar o vertex shader da possibilidade de ativar/desativar um efeito de deforma��o do modelo 3D
carregado. Esta deforma��o dever� variar em fun��o do tempo.
*/

// includes
#include "Object.h"
#include "Windowmanager.h"
#include "OpenGlState.h"

// define o tamanho da janela de visualiza�ao
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(void)
{
	// Starting
	std::cout << " ***** Starting *****\n";

#pragma region Vars
	// defini��o de objectos
	P3D::Object* obj_to_render_;	// define um novo objecto
	P3D::WindowManager* window_manager_;	// controlador de janelas

	// leitura do ficheiro
	char obj_path[256];	// caminha para o directorio
#pragma endregion Vars

	// inicia�ao para ler valores do ficheiro xyz
	// indica�ao do caminho do ficheiro
	std::cout << "Insert object directory: ";

	std::cin.clear();
	std::cin.get(obj_path, sizeof(obj_path) / sizeof(obj_path[0]));
	std::cout << "Checking file Directory..." << std::endl;

	// inicia a cria�ao de um objecto
	obj_to_render_ = new P3D::Object(obj_path);

	// confirma se o objecto foi carregado com sucesso
	if (!obj_to_render_->Validate())
		return -1; // caso nao existam vertices carregados, aborta o render

	// inicia uma nova janela
	window_manager_ = new P3D::WindowManager(("obj to render " + obj_to_render_->GetObjName()).c_str(),
		WINDOW_WIDTH, WINDOW_HEIGHT);

		// inicia o estado do GL
	P3D::StartStateGl(*window_manager_);


	// carrega objecto para memoria grafica
	obj_to_render_->LoadBuffers();	
	// carrega shaders para GPU
	if(!obj_to_render_->LoadShaders()) return 0;

	// liga os atributos �s propriedades do shader
	obj_to_render_->ConnectShaderValues();

	// informa que o ciclo de render foi iniciado
	std::cout << "\n === Render Cycle Started! ===" << std::endl;

	// ciclo de render
	while (!glfwWindowShouldClose(window_manager_->GetWindow()))
	{
		// limpa os buffers de cor e de profundidade
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// update logico

		// render Update


		// alterna os buffers
		glfwSwapBuffers(window_manager_->GetWindow());
		// chama eventos de janela e input
		glfwPollEvents();
	}

	// termina o espa�o glfw, destroi janelas e cursores ainda abertos
	P3D::CloseGL();

	// aguarda o input
	// ignora e limpa buffer de entrada actual
	std::cin.clear(); std::cin.ignore();

	system("pause");
	return 0;
}