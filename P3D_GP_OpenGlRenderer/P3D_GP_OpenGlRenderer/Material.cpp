#pragma once
#include "Material.h"

namespace P3D {

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
	// metodo chamado para carregar os valores do material para a GPU
	void Material::LoadMaterialProperties(GLint program) {
		// carrega os valores do material para o shader
		// valores do coeficiente de reflexao da luz ambiente
		glProgramUniform3fv(program, glGetUniformLocation(program, "MAT.KA_AMBIENT"), 1,
			glm::value_ptr(this->GetMaterialAmbienteVal()));
		// valores de coeficiente de reflexao da luz difusa
		glProgramUniform3fv(program, glGetUniformLocation(program, "MAT.KD_DIFUSE"), 1,
			glm::value_ptr(this->GetMaterialDifuseVal()));
		// valores de coeficiente de reflexao da luz especular
		glProgramUniform3fv(program, glGetUniformLocation(program, "MAT.KS_SPECULAR"), 1,
			glm::value_ptr(this->GetMaterialSpecularVal()));

		// valor de expoente especular
		glProgramUniform1f(program, glGetUniformLocation(program, "MAT.NS_SPECULAR"),
			this->GetSpecularExponentialVal());
		std::cout << GetSpecularExponentialVal() << std::endl;
		// informa que os valores do matrial foram associados ao shader
		std::cout << "Materials values setted on shader" << std::endl;
	}

#pragma region PrivateMethods
	// imprime informaçoes do material
	void Material::PrintInfo()
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