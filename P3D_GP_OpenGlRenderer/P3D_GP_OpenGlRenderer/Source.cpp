// Trabalho prático - Programaçao 3D
// renderer 3D para obj's -> material -> texture (tga file)
//	using VAO e 

/*
Fase 1[5 valores]:
(done) • Implementar a gestão de janelas e interface com o utilizador através da biblioteca GLFW;
(done) • Implementar a manipulação de matrizes e vetores através da biblioteca GLM;
(done) • A aplicação deverá permitir ao utilizador realizar zoom através da scroll wheel do rato;
(done) • A aplicação deverá permitir navegar, em torno do modelo 3D, através de movimentos do rato.

Fase 2 [6 valores]:
• Os alunos deverão desenvolver uma biblioteca C++ capaz de:
(done) o Carregar os dados de posição dos vértices, normais, e coordenadas de textura do ficheiro .xyz;
(done) o Enviar para a memória de GPU (VAO e respetivos VBOs) os dados dos vértices;
(done) o Identificar no ficheiro .xyz o nome do ficheiro .mtl;
(done) o Carregar as propriedades do material (ficheiro .mtl), incluindo a imagem de textura;
(done) o Carregar a imagem de textura para uma unidade de textura do OpenGL;
(done) o Disponibilizar função para renderização do objeto.
(done) • A aplicação deverá fazer uso dessa biblioteca C++ para carregar e renderizar o modelo 3D fornecido;

- Fase 3 [6 valores]:
(done)• Deverá ser possível aplicar uma qualquer combinação de 4 fontes de luz que incidam sobre o objeto:
(done)o Luz ambiente;
(done)o Luz direcional;
(done)o Luz pontual;
(done)o Luz cónica.
• Os parâmetros de cada uma das fontes de luz ficam ao critério de cada grupo;
(done)• A aplicação deverá permitir ao utilizador ativar/desativar cada fonte de luz, através de uma tecla:
(done)o ‘1’ – Ativar/desativar fonte de luz ambiente;
(done)o ‘2’ – Ativar/desativar fonte de luz direcional;
(done)o ‘3’ – Ativar/desativar fonte de luz pontual;
(done)o ‘4’ – Ativar/desativar fonte de luz cónica.

- Fase 4 [3 valores]:
(Done) • Dotar o vertex shader da possibilidade de ativar/desativar um efeito de deformação do modelo 3D
carregado. Esta deformação deverá variar em função do tempo.
*/

// includes
#include "OpenGlState.h"
#include "InputController.h"
#include "Light.h"

// define o tamanho da janela de visualizaçao
#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 800

int main(void)
{
	// Starting
	std::cout << " ***** Starting *****\n";

#pragma region Vars
	// definição de objectos
	P3D::Object* obj_to_render_;	// define um novo objecto
	P3D::WindowManager* window_manager_;	// controlador de janelas
	P3D::InputController* input_controller;	// controlador de input
	P3D::Light lights[4];		// array de luzes

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

#pragma region lightDef
	// inicia a criaçao das luzes
	P3D::InitLights(lights);
	// define os valores para cada uma das luzes
	// luz ambiente +++++++++++++
	// valores para luz ambiente
	lights[0].SetAmbientLightValue(	1.5f, 1.5f, 1.5f);
	// luz direcional ++++++++++++
	lights[1].SetLightDirection(	-1.0f, 0.0f, -1.0f);	// direcçao da luz
	lights[1].SetAmbientLightValue(	0.0f, 0.6f, 0.6f);		// componente ambiente
	lights[1].SetDifuseLightValue(	0.0f, 0.6f, 0.6f);		// componente difusa
	lights[1].SetSpecularLightValue(0.0f, 0.6f, 0.6f);		// componente especular
	// luz pontual +++++++++++++++
	lights[2].SetLightPosition(		-1.5f, 5.5f, -1.5f);		// posiçao da luz
	lights[2].SetAmbientLightValue(	1.6f, 1.6f, 0.5f);		// componente ambiente
	lights[2].SetDifuseLightValue(	1.6f, 1.6f, 0.5f);		// componente difusa
	lights[2].SetSpecularLightValue(1.6f, 1.6f, 0.5f);		// componente especular
	lights[2].SetAttenuationValues(	1.0f, 0.09f, 0.032f);	// constantes de atenuaçao
	// luz conica +++++++++++++++++
	lights[3].SetLightPosition(		0.0f, 2.8f, 5.5f);		// posiçao da luz
	lights[3].SetLightDirection(	0.0f, 0.0f, -1.0f);		// direcçao da luz
	lights[3].SetAmbientLightValue(	1.5f, 0.5f, 2.5f);		// componente ambiente
	lights[3].SetDifuseLightValue(	1.5f, 0.5f, 2.5f);		// componente difusa
	lights[3].SetSpecularLightValue(1.5f, 0.5f, 2.5f);		// componente especular
	lights[3].SetAttenuationValues(	1.0f, 0.09f, 0.032f);	// constantes de atenuaçao
	lights[3].SetLightExponentVal(	10.5f);					// valor exponencial de especular
	lights[3].SetLightCutOffAngle(	0.5f);					// angulo de cutOff
	lights[3].SetLightOutCutOffAngle(2.5f);					// angulo exterior de cutOff
#pragma endregion -> lightDef

	// define o controlador de intpu
	input_controller = new P3D::InputController(window_manager_, obj_to_render_, lights);

	// inicia o estado do GL
	P3D::StartStateGl(*window_manager_);

	// define os callbacks para o input
	input_controller->SetCallbacksFuncs();

	// carrega objecto para memoria grafica
	obj_to_render_->LoadBuffers();
	// carrega shaders para GPU
	if (!obj_to_render_->LoadShaders()) return 0;
	// liga os atributos ás propriedades do shader
	obj_to_render_->ConnectShaderValues();

	// liga valores da luz ao shader
	for (int i = 0; i < 4; i++) {
		lights[i].SetShaderLightValue(obj_to_render_->GetShaderProgram());
	}

	// liga atributos uniformes
	P3D::ConnectUniformValues(window_manager_, obj_to_render_, lights);

	// informa que o ciclo de render foi iniciado	e os controls
	std::cout << "\n-> Press E to enable/disable distortion" << std::endl;
	std::cout << "-> Press W/S to go up/down" << std::endl;
	std::cout << "-> Press '1' to enable/disable ambient light" << std::endl;
	std::cout << "-> Press '2' to enable/disable directional light" << std::endl;
	std::cout << "-> Press '3' to enable/disable point light" << std::endl;
	std::cout << "-> Press '4' to enable/disable cone light" << std::endl;

	// indica que o ciclo de jogo começou
	std::cout << "\n === Render Cycle Started! ===\n" << std::endl;

	// imprime as informaçoes das luzes
	for (int i = 0; i < 4; i++) {
		lights[i].DisplayLightInfo();
	}

	// ciclo de render
	while (!glfwWindowShouldClose(window_manager_->GetWindow())) {
		// update para valores de input
		input_controller->Update();

		// chama funçao de draw de GL, recebe o gestor de janela e o objecto a mostrar
		P3D::DrawGL(window_manager_, obj_to_render_, lights);
	}

	// termina o espaço glfw, destroi janelas e cursores ainda abertos
	P3D::CloseGL();
	// aguarda o input
	// ignora e limpa buffer de entrada actual
	std::cin.clear(); std::cin.ignore();

	system("pause");
	return 0;
}