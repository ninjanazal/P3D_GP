#pragma once
#include "OpenGlState.h"

namespace P3D
{
	// declera�ao da fun�ao de callback para erros
	void ErrorCallback(int error, const char* descripton);

	// inicia as luzes, 4, uma para cada tipo
	void InitLights(P3D::Light* lights)
	{
		// inicia cada uma das luzes
		lights[0] = P3D::Light(P3D::kLIGHTTYPE::kAmbiente);		// luz ambiente na pos 0
		lights[1] = P3D::Light(P3D::kLIGHTTYPE::kDirectional);	// luz direcional na pos 1
		lights[2] = P3D::Light(P3D::kLIGHTTYPE::kPoint);		// luz pontual na pos 2
		lights[3] = P3D::Light(P3D::kLIGHTTYPE::kCone);			// luz conica na pos 3
	}

	// fun�ao que inicia o estado do GL
	bool InitGLFW()
	{
		// informa o inicio da utiliza�ao
		std::cout << "\n\n\t\t====== Stating GLState =====\n\n" << std::endl;

		// define o callback para erros
		glfwSetErrorCallback(ErrorCallback);

		// informa a defini�ao
		std::cout << "Error callBack setted...\n\n-> Starting GLFW Lib..." << std::endl;

		// inicia a biblioteca
		if (!glfwInit()) {
			// informa que falhou o inicio do glfw
			std::cout << "Failed to initialize GLFW! Closing..." << std::endl;
			return false;
		}
		// concluido com sucesso, imprique que pode iniciar uma nova janela
		std::cout << "Ready to Start a new window!" << std::endl;
		// retorna 
		return true;
	}

	// fun�ao de fecho do estado de GL
	void CloseGL(void)
	{
		// decha termina o glfw
		glfwTerminate();
		// informa o fecho
		std::cout << "GLFW Terminated!" << std::endl;
	}

	// fun�ao de inicializa�ao do glew
	bool InitGLEW(void)
	{
		// Inicia o gestor de extens�es GLEW
		glewExperimental = GL_TRUE;

		// inicia o glew e avalia se foi correcta
		if (GLEW_OK == glewInit())	// avalia o resultado de glewInit
			return true;	// caso tenha retornado OK
		else {
			// informa que o inicio falhou
			std::cout << "Failed to initialize GLEW! Closing..." << std::endl;
			return false;	// caso tenha retornado !OK
		}
	}

	// imprime ionforma�ao do gl
	void PrintGlInformation(void)
	{
		// determina a versao do OpenGl em uso
		GLint major, minor;
		glGetIntegerv(GL_MAJOR_VERSION, &major);
		glGetIntegerv(GL_MINOR_VERSION, &minor);
		// imprime a versao determinada
		std::cout << "\nOpenGL version " << major << '.' << minor << std::endl;

		const GLubyte* glversion = glGetString(GL_VERSION);
		const GLubyte* glvendor = glGetString(GL_VENDOR);
		const GLubyte* glrenderer = glGetString(GL_RENDERER);
		std::cout << "\nVersion:  " << glversion << std::endl <<
			"Vendor:   " << glvendor << std::endl <<
			"Renderer: " << glrenderer << std::endl;

		std::cout << "\nSupported GLSL versions:\n";
		const GLubyte* glslversion = glGetString(GL_SHADING_LANGUAGE_VERSION);
		std::cout << "Higher supported version:\n" << glslversion << std::endl;
	}

	// define variaveis iniciais do OpenGL
	void InitOpenGL(void)
	{
		// define a cor a utilizar quando usado glClear
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		// activa o teste de profundidade
		glEnable(GL_DEPTH_TEST);
		// activa o culling de faces
		//glEnable(GL_CULL_FACE);
	}


	// fun�oes internas 
	// fun�ao de callback para erros
	void ErrorCallback(int error, const char* descripton) {
		// imprime o erro
		std::cout << "Error: " + error << " -> " << descripton << std::endl;
	}

	// fun�ao que inicia o estado do Gl
	bool StartStateGl(P3D::WindowManager& manager)
	{
		if (!P3D::InitGLFW())
			return 0;	// caso nao tenha iniciado correctamente, aborta

		// cria uma nova janela
		if (!manager.CreateWindow())
			return 0; // caso nao tenha conseguido criar uma janela, termina

		// define a janela como contexto actual
		glfwMakeContextCurrent(manager.GetWindow());

		// inicia o glew
		if (!P3D::InitGLEW())
			return 0;	// caso nao tenha iniciado correctamente, aborta

		// inicia valores de OpenGL
		P3D::InitOpenGL();
		// imprime informa�ao sobre o OpenGl em uso
		P3D::PrintGlInformation();

		// retorna que concluiu a prepara�ao
		return 1;
	}


	// liga valores uniformes
	void ConnectUniformValues(P3D::WindowManager* manager, P3D::Object* obj, P3D::Light* lights) {
		// valores uniformes gerais

		// ====== matriz MVP
		// determina a matrix mvp
		glm::mat4 mvp_matrix = manager->GetProjectionMat() * manager->GetViewMat() * obj->GetModelMat();
		// com o nome atribui o valor
		glProgramUniformMatrix4fv(obj->GetShaderProgram(), glGetProgramResourceLocation(obj->GetShaderProgram(), GL_UNIFORM, "_MVP"),
			1, GL_FALSE, glm::value_ptr(mvp_matrix));
		// atribui a matriz de modelo ao uniform
		glProgramUniformMatrix4fv(obj->GetShaderProgram(), glGetProgramResourceLocation(obj->GetShaderProgram(), GL_UNIFORM, "_MODEL"),
			1, GL_FALSE, glm::value_ptr(obj->GetModelMat()));

		// ============== camera Info ===============
		// atribui a posi�ao da camera ao uniform
		glProgramUniform3fv(obj->GetShaderProgram(), glGetUniformLocation(obj->GetShaderProgram(), "_VIEW_POS"),
			1, glm::value_ptr(manager->GetCameraPositon()));

		// atribui ao uniform _TIME, o tempo de execu�ao total do GL
		glProgramUniform1f(obj->GetShaderProgram(), glGetUniformLocation(obj->GetShaderProgram(), "_TIME"), float(glfwGetTime()));

		// actualiza o uniform da deforma�ao no shader
		glProgramUniform1i(obj->GetShaderProgram(), glGetUniformLocation(obj->GetShaderProgram(), "_ENABLE_DEFORMATION"),
			obj->GetDeformationvalue());

		// =============== Luz ==================
		// atualiza os valores
		for (int i = 0; i < 4; i++) {
			// para cada uma das luzes actualiza o seu estado
			lights[i].UpdateShaderLightState(obj->GetShaderProgram());
		}

	}

	// fun�ao de draw do GL
	void DrawGL(P3D::WindowManager* manager, P3D::Object* obj, P3D::Light* lights) {
		// Fun�ao de Draw
		// limpa os buffers de cor e de profundidade
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// update logico
		P3D::ConnectUniformValues(manager, obj, lights);

		// render Update
		// desenha o objecto
		obj->Drawobj();

		// alterna os buffers
		glfwSwapBuffers(manager->GetWindow());
		// chama eventos de janela e input
		glfwPollEvents();
	}

}