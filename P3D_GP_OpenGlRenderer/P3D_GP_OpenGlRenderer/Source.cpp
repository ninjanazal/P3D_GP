// Trabalho pr�tico - Programa�ao 3D
// renderer 3D para obj's -> material -> texture (tga file)
//	using VAO e 

/*
Fase 1[5 valores]:
(done) � Implementar a gest�o de janelas e interface com o utilizador atrav�s da biblioteca GLFW;
(done) � Implementar a manipula��o de matrizes e vetores atrav�s da biblioteca GLM;
(done) � A aplica��o dever� permitir ao utilizador realizar zoom atrav�s da scroll wheel do rato;
(done) � A aplica��o dever� permitir navegar, em torno do modelo 3D, atrav�s de movimentos do rato.

Fase 2 [6 valores]:
� Os alunos dever�o desenvolver uma biblioteca C++ capaz de:
(done) o Carregar os dados de posi��o dos v�rtices, normais, e coordenadas de textura do ficheiro .xyz;
(done) o Enviar para a mem�ria de GPU (VAO e respetivos VBOs) os dados dos v�rtices;
(done) o Identificar no ficheiro .xyz o nome do ficheiro .mtl;
(done) o Carregar as propriedades do material (ficheiro .mtl), incluindo a imagem de textura;
(done) o Carregar a imagem de textura para uma unidade de textura do OpenGL;
(done) o Disponibilizar fun��o para renderiza��o do objeto.
(done) � A aplica��o dever� fazer uso dessa biblioteca C++ para carregar e renderizar o modelo 3D fornecido;

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
#include "OpenGlState.h"
#include "InputController.h"

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
	P3D::InputController* input_controller;	// controlador de input

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

	// define o controlador de intpu
	input_controller = new P3D::InputController(window_manager_, obj_to_render_);

	// inicia o estado do GL
	P3D::StartStateGl(*window_manager_);

	// define os callbacks para o input
	input_controller->SetCallbacksFuncs();

	// carrega objecto para memoria grafica
	obj_to_render_->LoadBuffers();
	// carrega shaders para GPU
	if (!obj_to_render_->LoadShaders()) return 0;
	// liga os atributos �s propriedades do shader
	obj_to_render_->ConnectShaderValues();

	// liga atributos uniformes
	P3D::ConnectUniformValues(window_manager_, obj_to_render_);

	// informa que o ciclo de render foi iniciado	e os controls
	std::cout << "\n-> Press E to enable/disable distortion" << std::endl;
	std::cout << "\n === Render Cycle Started! ===" << std::endl;

	// ciclo de render
	while (!glfwWindowShouldClose(window_manager_->GetWindow())) {
		// update para valores de input
		input_controller->Update();

		// chama fun�ao de draw de GL, recebe o gestor de janela e o objecto a mostrar
		P3D::DrawGL(window_manager_, obj_to_render_);
	}

	// termina o espa�o glfw, destroi janelas e cursores ainda abertos
	P3D::CloseGL();
	// aguarda o input
	// ignora e limpa buffer de entrada actual
	std::cin.clear(); std::cin.ignore();

	system("pause");
	return 0;
}