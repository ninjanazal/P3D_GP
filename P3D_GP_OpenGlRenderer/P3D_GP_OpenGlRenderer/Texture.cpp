#pragma once
#include "Texture.h"

namespace P3D {
	// construtor, recebe o nome da textura e o directorio
	Texture::Texture(const char* tex_name, const char* dir) :
		tex_name(tex_name), directory_(dir)
	{
		// inicia o carregamento das informaçoes
		// indica o tamanho da textura em bytes
		this->image_data = P3D::LoadTextureValues((this->directory_ + this->tex_name).c_str(), this->tex_width,
			this->tex_height, this->tex_channels);
	}

	// Carregamento da textura para a GPU
	void Texture::LoadTextureBuffer(void)
	{
		// informa que a alocaçao da textura na gpu foi iniciada
		std::cout << "Passing texture data to GPU..." << std::endl;

		// sabendo que apenas uma textura vai ser utilizada
		// gera o nome que vai ser atribuido a esta, passado a referencia
		glGenTextures(GLuint(1), this->image_name);

		// bind, inicia a alucaçao de mem para a textura
		glBindTexture(GL_TEXTURE_2D, this->image_name[0]);

		// define os parametros da imager
		// parametros de wrap
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		// parametros de minificaçao e magnificaçao
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// carrega para memoria grafica a informaçao da textura
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8,
			this->tex_width, this->tex_height, 0, this->tex_channels == 4 ? GL_RGBA : GL_RGB,
			GL_UNSIGNED_BYTE, this->image_data);

		// liberta a informaçao dos pixeis da imagem
		stbi_image_free(this->image_data);

		// informa que terminoun de carrega os dados de textura para a gpu
		std::cout << "Finished passing Texture data!" << std::endl;
	}

	// liga valores da textura ao shader
	void Texture::ConnectTextureShaderValue(GLint program) {
		// activa o espaço de imagem na gpu para a slot 0, visto que só existe uma imagem para o modelo
		glActiveTexture(GL_TEXTURE0);
		// vincula a unidade de textura
		glBindTexture(GL_TEXTURE_2D, this->image_name[0]);
		// define o interiro de sampler, indica qual a textura que deve ser usada no shader (sampler2D)
		glProgramUniform1i(program, glGetUniformLocation(program, "obj_texture"), 0);

	}

}