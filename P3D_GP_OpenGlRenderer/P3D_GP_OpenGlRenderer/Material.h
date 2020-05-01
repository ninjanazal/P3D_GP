#pragma once
// sao incluidas e definidas todas as librarias externas visto que todo o programa dependerá 
// maioritariamente, occorendo aqui grande parte da transformaçao do mesmo
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
#include <vector>
#include <string>

#define GLEW_STATIC
#include <GL\glew.h>

#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

#include "FileFuncs.h" //include de funçoes de leitura


// namespace para o projecto
namespace P3D
{
	class Material
	{
	public:

		Material() {};	// construtor semp parametros
		Material(const char*, const char*);	// construtor, recebe o nome do material e o directorio
		~Material();	// destrutor da classe

#pragma region Getters
		std::string GetMaterialName(void) { return mat_name; };	// retorna o nome do objecto
		glm::vec3 GetMaterialAmbienteVal(void) { return coeficients[0]; };	// retorna o valor do coeficiente reflexao ambiente
		glm::vec3 GetMaterialDifuseVal(void) { return coeficients[1]; };	// retorna o valor de coeficiente reflexao difusa
		glm::vec3 GetMaterialSpecularVal(void) { return coeficients[2]; };	// retorna o valor de coeficiente reflexao especular

		GLfloat GetSpecularExponentialVal(void) { return specular_exponential; };	// retorna valor de expoente especular
#pragma endregion Getters

	private:
		std::string mat_name, directory_, texture_name;	// nome do material, directoria, e nome da textura
		glm::vec3 coeficients[3]{};	// valores de coeficientes
		float specular_exponential;	// expoente especular

		// metodos privados
		void PrintInfo();	// imprime dados do material
	};

	// construtor de class Material, recebe nome e directorio do material
	Material::Material(const char* MatName, const char* dir)
	{
		this->mat_name = MatName;	// guarda o nome do material	
		this->directory_ = dir;		// guarda o caminho para o directorio

		// avalia se o caminho para o ficheiro é valido
		if (P3D::ConfirmFile((this->directory_ + this->mat_name).c_str()))
		{
			// caso, indica que inicia a leitura do ficheiro
			std::cout << "Start loading meterial file..." << std::endl;

			// chama a leitura de ficheiro dos dados do material
			texture_name =
				P3D::LoadObjMaterialValues((this->directory_ + this->mat_name).c_str(), this->coeficients,
					this->specular_exponential);

			// gua
			// imprime as informaçoes carregadas
			PrintInfo();

			// avalia se alguma textura foi retornada
			if (!texture_name.empty())
			{
				// caso exista uma textura retornada

			}
		}
	}

	Material::~Material()
	{
	}


#pragma region PrivateMethods
	// imprime informaçoes do material
	void Material::PrintInfo()
	{
		// imprime dados do material
		std::cout << "Material -> " << mat_name << std::endl;	// imprime o nome
		// para cada um dos tipos de coeficientes
		for (int i = 0; i < 3; i++) {
			switch (i) {
			case 0:	// para o coeficiente de luz ambiente
				std::cout << "Ambiente light coef:";
				break;
			case 1:	// para coeficienbte de luz difusa
				std::cout << "Difuse light coef: ";
				break;
			case 2: // para coeficiente de luz especular
				std::cout << "Specular light coef: ";
				break;
			}
			// imprime o valor para o coeficiente 
			std::cout << "x: " << coeficients[i].x << " y: " << coeficients[i].y <<
				" z: " << coeficients[i].z << std::endl;			
		}

		// imprime o expoente especular
		std::cout << "Specular exponent: " << specular_exponential << std::endl;
		// imprime o nome da textura, caso exista
		if (!texture_name.empty())
			std::cout << "Texture Map: " << texture_name << std::endl;
	}
#pragma endregion

}