#pragma once
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
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...

#include <iostream>
#include <string>
#include <vector>

#include "FileFuncs.h" //include de funçoes de leitura


// utilizaçao do namespace
namespace P3D
{
	class Texture
	{
	public:
		Texture(const char*, const char*);	// construtor da class, recebe, nome e directorio
		~Texture();	// destrutor da class

		// Funcs
		// Carrega textura para buffer da GPU
		void LoadTextureBuffer(void);
		// liga ao shader o atributo da textura
		void ConnectTextureShaderValue(GLint program);

	private:
		// informaçao da textura
		std::string tex_name, directory_;
		unsigned char * image_data;	// informaçao da textura
		GLint tex_width, tex_height, tex_channels;	// info da altura, largura e canais

		// render information
		GLuint image_name[1]{};	// nome atribuido á textura 
	};
}