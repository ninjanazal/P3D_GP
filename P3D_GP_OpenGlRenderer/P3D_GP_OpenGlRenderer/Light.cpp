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
			std::cout << "light values: " << ambient_light_value[0] << " : " << ambient_light_value[1] <<
				" : " << ambient_light_value[2] << std::endl;
			break;
			// caso seja uma luz direcional
		case kLIGHTTYPE::kDirectional:
			// informaçoes da luz
			std::cout << "--> Directional Light <--" << std::endl;
			std::cout << "light direction: " << light_direction[0] << " : " << light_direction[1] << " : " <<
				light_direction[2] << std::endl;
			break;
			// caso seja uma luz pontual
		case kLIGHTTYPE::kPoint:
			// informaçoes da luz
			std::cout << "--> Point Light <--" << std::endl;
			std::cout << "light position: " << light_position[0] << " : " << light_position[1] << " : " <<
				light_position[2] << std::endl;
			std::cout << "Attenuation values :: constant-> " << this->constant << " :: linear-> " << this->linear <<
				" :: quadratic-> " << this->quadratic << std::endl;
			break;
			// caso seja uma luz conica
		case kLIGHTTYPE::kCone:
			std::cout << "--> Spot Light <--" << std::endl;
			std::cout << "light position: " << light_position[0] << " : " << light_position[1] << " : " <<
				light_position[2] << std::endl;
			std::cout << "light direction: " << light_direction[0] << " : " << light_direction[1] << " : " <<
				light_direction[2] << std::endl;
			std::cout << "Attenuation values :: constant-> " << this->constant << " :: linear-> " << this->linear <<
				" :: quadratic-> " << this->quadratic << std::endl;
			std::cout << "Spot values :: Exponet-> " << this->exponent_val << " :: CutOffValue-> " << glm::degrees(this->cutoff_angle) << std::endl;
			break;
		default:
			// caso nao tenha o tipo definido
			std::cout << "No light type found!" << std::endl;
			break;
		}
	}
	// activa ou desativa a luz 
	void Light::EnableLight() { enable = !enable; }



	// define a componente ambiente da luz
	void Light::SetAmbientLightValue(float r, float g, float b) {
		// guarda os valores do componente
		ambient_light_value[0] = r;
		ambient_light_value[1] = g;
		ambient_light_value[2] = b;
	}
	// define a componente difusa da luz
	void Light::SetDifuseLightValue(float r, float g, float b) {
		// guarda os valores da componente
		difuse_light_value[0] = r;
		difuse_light_value[1] = g;
		difuse_light_value[2] = b;
	}
	// define a componente especular da luz
	void Light::SetSpecularLightValue(float r, float g, float b) {
		// guarda os valores da componente
		specular_light_value[0] = r;
		specular_light_value[1] = g;
		specular_light_value[2] = b;
	}

	// define a direcçao da luz
	void Light::SetLightDirection(float x, float y, float z) {
		// guarda os valores da direcçao
		light_direction[0] = x;
		light_direction[1] = y;
		light_direction[2] = z;
	}
	// define a posiçao da luz
	void Light::SetLightPosition(float x, float y, float z) {
		// guarda os valores para a posiçao
		light_position[0] = x;
		light_position[1] = y;
		light_position[2] = z;
	}
	
	// define as constantes de atenuaçao da luz
	void Light::SetAttenuationValues(float constant, float linear, float quadratic) {
		// guarda os valores 
		this->constant = constant;
		this->linear = linear;
		this->quadratic = quadratic;
	}
	//define o valor de expoente da luz conica
	void Light::SetLightExponentVal(float exponet) {
		// guarda o valor
		this->exponent_val = exponet;
	}
	// define o angulo de cutOff recebe graus e e ajusta para valores de produto escalar
	void Light::SetLightCutOffAngle(float angle_degrees) {
		// guarda o valor em radianos
		this->cutoff_angle = glm::radians(angle_degrees);
	}

	// define valores da luz no shader
	void Light::SetShaderLightValue(GLint shader_program) {
		// para cada uma das luzer
		switch (this->light_type) {
			// caso seja uma luz ambiente
		case kLIGHTTYPE::kAmbiente:
			// define o estado da luz
			glProgramUniform1i(shader_program, glGetUniformLocation(shader_program, "AMBIENTLIGHT._ENABLE"), enable);
			//define o valor da luz no uniform
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "AMBIENTLIGHT._COLOR"), 1, ambient_light_value);
			break;
			// caso seja uma luz direcional
		case kLIGHTTYPE::kDirectional:
			// define o estado da luz
			glProgramUniform1i(shader_program, glGetProgramResourceLocation(shader_program, GL_UNIFORM, "DIRECTIONALLIGHT._ENABLE"), enable);
			// define a direcçao da luz
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "DIRECTIONALLIGHT._DIRECTION"), 1, light_direction);
			// define o valor da componente ambiente
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "DIRECTIONALLIGHT._AMBIENT_COMP"), 1, ambient_light_value);
			// define o valor da componente difusa
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "DIRECTIONALLIGHT._DIFFUSE_COMP"), 1, difuse_light_value);
			// define o valor da componente especular
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "DIRECTIONALLIGHT._SPECULAR_COMP"), 1, specular_light_value);
			break;
			// caso seja uma luz pontual
		case kLIGHTTYPE::kPoint:
			// define o estado da luz
			glProgramUniform1i(shader_program, glGetProgramResourceLocation(shader_program, GL_UNIFORM, "POINTLIGHT._ENABLE"), enable);
			// define a posiçao da luz
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "POINTLIGHT._POSITION"), 1, light_position);
			// define o valor da componente ambiente
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "POINTLIGHT._AMBIENT_COMP"), 1, ambient_light_value);
			// define o valor da componente difusa
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "POINTLIGHT._DIFFUSE_COMP"), 1, difuse_light_value);
			// define o valor da componente especular
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "POINTLIGHT._SPECULAR_COMP"), 1, specular_light_value);
			// define o valor da constante de atenuaçao
			glProgramUniform1f(shader_program, glGetUniformLocation(shader_program, "POINTLIGHT._CONSTANT_VAL"), constant);
			// define o valor linear de atenuaçao
			glProgramUniform1f(shader_program, glGetUniformLocation(shader_program, "POINTLIGHT._LINEAR_VAL"), linear);
			// define o valor quadratico de atenuaçao
			glProgramUniform1f(shader_program, glGetUniformLocation(shader_program, "POINTLIGHT._QUADRATIC_VAL"), quadratic);
			break;
			// caso seja uma luz conica
		case kLIGHTTYPE::kCone:
			// define o estado da luz
			glProgramUniform1i(shader_program, glGetProgramResourceLocation(shader_program, GL_UNIFORM, "SPOTLIGHT._ENABLE"), enable);
			// define a posiçao da luz
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "SPOTLIGHT._POSITION"), 1, light_position);
			// define a direcçao da luz
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "SPOTLIGHT._DIRECTION"), 1, light_direction);
			// define o valor da componente ambiente
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "SPOTLIGHT._AMBIENT_COMP"), 1, ambient_light_value);
			// define o valor da componente difusa
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "SPOTLIGHT._DIFFUSE_COMP"), 1, difuse_light_value);
			// define o valor da componente especular
			glProgramUniform3fv(shader_program, glGetUniformLocation(shader_program, "SPOTLIGHT._SPECULAR_COMP"), 1, specular_light_value);
			// define o valor da constante de atenuaçao
			glProgramUniform1f(shader_program, glGetUniformLocation(shader_program, "SPOTLIGHT._CONSTANT_VAL"), constant);
			// define o valor linear de atenuaçao
			glProgramUniform1f(shader_program, glGetUniformLocation(shader_program, "SPOTLIGHT._LINEAR_VAL"), linear);
			// define o valor quadratico de atenuaçao
			glProgramUniform1f(shader_program, glGetUniformLocation(shader_program, "SPOTLIGHT._QUADRATIC_VAL"), quadratic);
			// define o valor do expoente de reflexao
			glProgramUniform1f(shader_program, glGetUniformLocation(shader_program, "SPOTLIGHT._EXPONENT_VAL"), exponent_val);
			// define o valor do cutoff 
			glProgramUniform1f(shader_program, glGetUniformLocation(shader_program, "SPOTLIGHT._CUTOFF_ANGLE"), cutoff_angle);
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
			// define o estado da luz
			glProgramUniform1i(shader_program, glGetProgramResourceLocation(shader_program, GL_UNIFORM, "DIRECTIONALLIGHT._ENABLE"), enable);
			break;
			// caso seja uma luz pontual
		case kLIGHTTYPE::kPoint:
			// define o estado da luz
			glProgramUniform1i(shader_program, glGetProgramResourceLocation(shader_program, GL_UNIFORM, "POINTLIGHT._ENABLE"), enable);
			break;
		case kLIGHTTYPE::kCone:
			// define o estado da luz
			glProgramUniform1i(shader_program, glGetProgramResourceLocation(shader_program, GL_UNIFORM, "SPOTLIGHT._ENABLE"), enable);
			break;
		default:
			// caso nao tenha o tipo definido
			std::cout << "No light type found!" << std::endl;
			break;
		}
	}
}
