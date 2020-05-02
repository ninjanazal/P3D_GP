#pragma once
// sao incluidas e definidas todas as librarias externas visto que todo o programa depender� 
// maioritariamente, occorendo aqui grande parte da transforma�ao do mesmo
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glew32s.lib"

#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr
#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...

#include <iostream>
#include <string>
#include <vector>

#include "FileFuncs.h" //include de fun�oes de leitura


// utiliza�ao do namespace
namespace P3D
{
	class Texture
	{
	public:
		Texture(const char*, const char*);	// construtor da class, recebe, nome e directorio
		~Texture() {};	// destrutor da class

		// Funcs
		// Carrega textura para buffer da GPU
		void LoadTextureBuffer(void);
#pragma 

	private:
		// informa�ao da textura
		std::string tex_name, directory_;
		unsigned char* image_data;	// informa�ao da textura
		GLint tex_width, tex_height, tex_channels;	// info da altura, largura e canais

		// render information
		GLuint image_name;	// nome atribuido � textura 
	};

	// construtor, recebe o nome da textura e o directorio
	Texture::Texture(const char* tex_name, const char* dir)
	{
		this->tex_name = tex_name;	// guarda o nome da textura
		this->directory_ = dir;		// guarda o path para o directorio

		// inicia o carregamento das informa�oes
		P3D::LoadTextureValues((this->directory_ + this->tex_name).c_str());
	}

	// Carregamento da textura para a GPU
	void Texture::LoadTextureBuffer(void)
	{
		// informa que a aloca�ao da textura na gpu foi iniciada
		std::cout << "Passing texture data to GPU..." << std::endl;

		// sabendo que apenas uma textura vai ser utilizada
		// gera o nome que vai ser atribuido a esta, passado a referencia
		glGenTextures(GLuint(1), &this->image_name);

		// bind, inicia a aluca�ao de mem para a textura
		glBindTexture(GL_TEXTURE_2D, this->image_name);


		// informa que terminoun de carrega os dados de textura para a gpu
		std::cout << "Finished passing Texture data!" << std::endl;
	}
}