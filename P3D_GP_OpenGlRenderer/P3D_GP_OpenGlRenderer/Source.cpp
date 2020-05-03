// Trabalho prático - Programaçao 3D
// renderer 3D para obj's -> material -> texture (tga file)
//	using VAO e 

/*
Fase 1[5 valores]:
• Implementar a gestão de janelas e interface com o utilizador através da biblioteca GLFW;
• Implementar a manipulação de matrizes e vetores através da biblioteca GLM;
•(2) Implementar a renderização de um cubo através da biblioteca OpenGL(incluindo a GLEW);
•(2) A coloração dos fragmentos do cubo deve ser realizada de modo a que cada face apresente uma cor
	distinta(nota que não é esperado que nesta fase estejam implementados os efeitos de iluminação);
• A aplicação deverá permitir ao utilizador realizar zoom através da scroll wheel do rato;
• A aplicação deverá permitir navegar, em torno do modelo 3D, através de movimentos do rato.

Fase 2 [6 valores]:
• Os alunos deverão desenvolver uma biblioteca C++ capaz de:
o Carregar os dados de posição dos vértices, normais, e coordenadas de textura do ficheiro .xyz;
o Enviar para a memória de GPU (VAO e respetivos VBOs) os dados dos vértices;
o Identificar no ficheiro .xyz o nome do ficheiro .mtl;
o Carregar as propriedades do material (ficheiro .mtl), incluindo a imagem de textura;
o Carregar a imagem de textura para uma unidade de textura do OpenGL;
o Disponibilizar função para renderização do objeto.
• A aplicação deverá fazer uso dessa biblioteca C++ para carregar e renderizar o modelo 3D fornecido;

- Fase 3 [6 valores]:
• Deverá ser possível aplicar uma qualquer combinação de 4 fontes de luz que incidam sobre o objeto:
o Luz ambiente;
o Luz direcional;
o Luz pontual;
o Luz cónica.
• Os parâmetros de cada uma das fontes de luz ficam ao critério de cada grupo;
• A aplicação deverá permitir ao utilizador ativar/desativar cada fonte de luz, através de uma tecla:
o ‘1’ – Ativar/desativar fonte de luz ambiente;
o ‘2’ – Ativar/desativar fonte de luz direcional;
o ‘3’ – Ativar/desativar fonte de luz pontual;
o ‘4’ – Ativar/desativar fonte de luz cónica.

- Fase 4 [3 valores]:
• Dotar o vertex shader da possibilidade de ativar/desativar um efeito de deformação do modelo 3D
carregado. Esta deformação deverá variar em função do tempo.
*/

// includes
#include "Object.h"
#include "Windowmanager.h"
#include "OpenGlState.h"

// define o tamanho da janela de visualizaçao
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(void)
{
	// Starting
	std::cout << " ***** Starting *****\n";

#pragma region Vars
	// definição de objectos
	P3D::Object* obj_to_render_;	// define um novo objecto
	P3D::WindowManager* window_manager_;	// controlador de janelas

	// leitura do ficheiro
	char obj_path[256];	// caminha para o directorio
#pragma endregion Vars

	// iniciaçao para ler valores do ficheiro xyz
	// indicaçao do caminho do ficheiro
	std::cout << "Insert object directory: ";

	std::cin.clear();
	std::cin.get(obj_path, sizeof(obj_path) / sizeof(obj_path[0]));
	std::cout << "Checking file Directory..." << std::endl;

	// inicia a criaçao de um objecto
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

	// liga os atributos ás propriedades do shader
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

	// termina o espaço glfw, destroi janelas e cursores ainda abertos
	P3D::CloseGL();

	// aguarda o input
	// ignora e limpa buffer de entrada actual
	std::cin.clear(); std::cin.ignore();

	system("pause");
	return 0;
}