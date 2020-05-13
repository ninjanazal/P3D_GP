#pragma once
#include "Texture.h"	// inclui def de textura

// namespace para o projecto
namespace P3D
{
	class Material 
	{
	public:

		Material() {};	// construtor semp parametros
		Material(const char*, const char*);	// construtor, recebe o nome do material e o directorio

		~Material() {};	// destrutor da classe

		// informaçao publica
		// metodo liga valores carregados com estruturas do shader
		void LoadMaterialProperties(GLint program);

		// informaçao da textura
		P3D::Texture* material_texture;


#pragma region Getters
		std::string GetMaterialName(void) { return mat_name; };	// retorna o nome do objecto
		glm::vec3 GetMaterialAmbienteVal(void) { return coeficients[0]; };	// retorna o valor do coeficiente reflexao ambiente
		glm::vec3 GetMaterialDifuseVal(void) { return coeficients[1]; };	// retorna o valor de coeficiente reflexao difusa
		glm::vec3 GetMaterialSpecularVal(void) { return coeficients[2]; };	// retorna o valor de coeficiente reflexao especular

		GLfloat GetSpecularExponentialVal(void) { return specular_exponential; };	// retorna valor de expoente especular
#pragma endregion Getters

	private:
		// informaçao do material
		std::string mat_name, directory_;	// nome do material, directoria, e nome da textura
		glm::vec3 coeficients[3]{};	// valores de coeficientes
		float specular_exponential;	// expoente especular


		// metodos privados
		inline void PrintInfo();	// imprime dados do material
	};
}