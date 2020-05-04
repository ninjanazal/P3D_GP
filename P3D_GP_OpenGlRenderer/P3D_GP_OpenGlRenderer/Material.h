#pragma once
#include "Texture.h"	// inclui def de textura

// namespace para o projecto
namespace P3D
{
	class Material 
	{
	public:

		inline Material() {};	// construtor semp parametros
		inline Material(const char*, const char*);	// construtor, recebe o nome do material e o directorio
		inline ~Material();	// destrutor da classe

		// informaçao publica
		// informaçao da textura
		P3D::Texture* material_texture;


#pragma region Getters
		inline std::string GetMaterialName(void) { return mat_name; };	// retorna o nome do objecto
		inline glm::vec3 GetMaterialAmbienteVal(void) { return coeficients[0]; };	// retorna o valor do coeficiente reflexao ambiente
		inline glm::vec3 GetMaterialDifuseVal(void) { return coeficients[1]; };	// retorna o valor de coeficiente reflexao difusa
		inline glm::vec3 GetMaterialSpecularVal(void) { return coeficients[2]; };	// retorna o valor de coeficiente reflexao especular

		GLfloat GetSpecularExponentialVal(void) { return specular_exponential; };	// retorna valor de expoente especular
#pragma endregion Getters

	private:
		// informaçao do material
		std::string mat_name, directory_;	// nome do material, directoria, e nome da textura
		glm::vec3 coeficients[3]{};	// valores de coeficientes
		float specular_exponential;	// expoente especular


		// metodos privados
		inline inline void PrintInfo();	// imprime dados do material
	};

	// construtor de class Material, recebe nome e directorio do material
	inline Material::Material(const char* MatName, const char* dir)
	{
		this->mat_name = MatName;	// guarda o nome do material	
		this->directory_ = dir;		// guarda o caminho para o directorio

		// avalia se o caminho para o ficheiro é valido
		if (P3D::ConfirmFile((this->directory_ + this->mat_name).c_str()))
		{
			// caso, indica que inicia a leitura do ficheiro
			std::cout << "Start loading meterial file..." << std::endl;

			// chama a leitura de ficheiro dos dados do material
			std::string texture_name =
				P3D::LoadObjMaterialValues((this->directory_ + this->mat_name).c_str(), this->coeficients,
					this->specular_exponential);

			// gua
			// imprime as informaçoes carregadas
			PrintInfo();

			// avalia se alguma textura foi retornada
			if (P3D::ConfirmFile((this->directory_ + texture_name).c_str()))
			{
				// caso exista uma textura retornada
				// indica que existe uma textura disponivel definida no material
				std::cout << "Texture file detected -> " << texture_name << std::endl;
				// indica que é iniciado a leitura de dados da textura
				std::cout << "Setting Texture data..." << std::endl;
				// define uma nova textura
				material_texture = new P3D::Texture(texture_name.c_str(), this->directory_.c_str());
			}
		}
	}

	inline Material::~Material()
	{
	}


#pragma region PrivateMethods
	// imprime informaçoes do material
	inline void Material::PrintInfo()
	{
		// imprime dados do material
		std::cout << "\n\n\t*** Material Info ***\nMaterial -> " << mat_name << std::endl;	// imprime o nome
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
	}
#pragma endregion

}