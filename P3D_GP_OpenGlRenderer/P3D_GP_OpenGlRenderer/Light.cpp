#include "Light.h"

namespace P3D {

	// construtor de class
	P3D::Light::Light(kLIGHTTYPE type) : light_type(type) {
		// guarda o valor da luz
	}
	// apresenta as informaçoes da luz
	void Light::DisplayLightInfo() {
		switch (this->light_type) {
			// caso seja uma luz ambiente
		case kLIGHTTYPE::kAmbiente:
			// informaçoes da luz
			std::cout << "--> Ambient Light <--" << std::endl;
			std::cout << "light values: " << light_value[0] << " : " << light_value[1] <<
				" : " << light_value[2] << std::endl;
			break;
			// caso seja uma luz direcional
		case kLIGHTTYPE::kDirectional:
			break;
			// caso seja uma luz pontual
		case kLIGHTTYPE::kPoint:
			break;
			// caso seja uma luz conica
		case kLIGHTTYPE::kCone:
			break;
		default:
			// caso nao tenha o tipo definido
			std::cout << "No light type found!" << std::endl;
			break;
		}
	}
	// activa ou desativa a luz 
	void Light::EnableLight() { enable = !enable; }



	// define a cor da luz
	void Light::SetLightValue(float r, float g, float b) {
		// guarda os valores de cor
		light_value[0] = r;
		light_value[1] = g;
		light_value[2] = b;
	}

	// define valores da luz no shader
	void Light::SetShaderLightValue(GLint shader_program) {
		// para cada uma das luzer
		switch (this->light_type) {
			// caso seja uma luz ambiente
		case kLIGHTTYPE::kAmbiente:
			//define o valor da luz no uniform
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "AMBIENTLIGHT._COLOR"), 1, light_value);
			// define o estado da luz
			glProgramUniform1i(shader_program, glGetUniformLocation(shader_program, "AMBIENTLIGHT._ENABLE"), enable);
			break;
			// caso seja uma luz direcional
		case kLIGHTTYPE::kDirectional:
			break;
			// caso seja uma luz pontual
		case kLIGHTTYPE::kPoint:
			break;
			// caso seja uma luz conica
		case kLIGHTTYPE::kCone:
			break;
		default:
			// caso nao tenha o tipo definido
			std::cout << "No light type found!" << std::endl;
			break;
		}
	}
	// actualiza o estado da luz no shader
	void Light::UpdateShaderLightState(GLint shader_program) {
		// para cada uma das luzer
		switch (this->light_type) {
			// caso seja uma luz ambiente
		case kLIGHTTYPE::kAmbiente:
			// define o estado da luz
			glProgramUniform1i(shader_program, glGetUniformLocation(shader_program, "AMBIENTLIGHT._ENABLE"), enable);
			break;
			// caso seja uma luz direcional
		case kLIGHTTYPE::kDirectional:
			break;
			// caso seja uma luz pontual
		case kLIGHTTYPE::kPoint:
			break;
			// caso seja uma luz conica
		case kLIGHTTYPE::kCone:
			break;
		default:
			// caso nao tenha o tipo definido
			std::cout << "No light type found!" << std::endl;
			break;
		}
	}
}
