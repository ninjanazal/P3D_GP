#pragma once
#include "OpenGlState.h"
#include "CallBacksDeff.h"

namespace P3D
{
	// fun�ao que inicia o estado do GL
	bool InitGLFW()
	{
		// informa o inicio da utiliza�ao
		std::cout << "\n\n\t\t====== Stating GLState =====\n\n" << std::endl;

		// define o callback para erros
		glfwSetErrorCallback(P3D::DisplayErrorCallback);

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
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		// activa o teste de profundidade
		glEnable(GL_DEPTH_TEST);
		// activa o culling de faces
		glEnable(GL_CULL_FACE);
	}
}