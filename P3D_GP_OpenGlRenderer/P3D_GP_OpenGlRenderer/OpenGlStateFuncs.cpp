#pragma once
#include "OpenGlState.h"

namespace P3D
{
	// decleraçao da funçao de callback para erros
	void ErrorCallback(int error, const char* descripton);


	// funçao que inicia o estado do GL
	bool InitGLFW()
	{
		// informa o inicio da utilizaçao
		std::cout << "\n\n\t\t====== Stating GLState =====\n\n" << std::endl;

		// define o callback para erros
		glfwSetErrorCallback(ErrorCallback);

		// informa a definiçao
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

	// funçao de fecho do estado de GL
	void CloseGL(void)
	{
		// decha termina o glfw
		glfwTerminate();
		// informa o fecho
		std::cout << "GLFW Terminated!" << std::endl;
	}

	// funçao de inicializaçao do glew
	bool InitGLEW(void)
	{
		// Inicia o gestor de extensões GLEW
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

	// imprime ionformaçao do gl
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
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// activa o teste de profundidade
		glEnable(GL_DEPTH_TEST);
		// activa o culling de faces
		glEnable(GL_CULL_FACE);
	}


	// funçoes internas 
	// funçao de callback para erros
	void ErrorCallback(int error, const char* descripton) {
		// imprime o erro
		std::cout << "Error: " + error << " -> " << descripton << std::endl;
	}

	// funçao que inicia o estado do Gl
	bool StartStateGl(P3D::WindowManager &manager)
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
		// imprime informaçao sobre o OpenGl em uso
		P3D::PrintGlInformation();

		// retorna que concluiu a preparaçao
		return 1;
	}
}