#ifndef LIGHT_H
#define LIGHT_H

// sao incluidas e definidas todas as librarias externas visto que todo o programa depender� 
// maioritariamente, occorendo aqui grande parte da transforma�ao do mesmo
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

namespace P3D {
	// enumerado com o tipo de lyz
	enum class kLIGHTTYPE { kAmbiente, kDirectional, kPoint, kCone };

	// class light
	class Light
	{
	public:
		Light() {};	// construtor padrao
		Light(kLIGHTTYPE type);		// construtor da class com tipo de luz
		~Light() {};				// destrutor da class

		// fun�oes para a defini�ao da luz
		void EnableLight();
		// imprime os valores da luz
		void DisplayLightInfo();

		// defini�ao da componente ambiente da luz
		void SetAmbientLightValue(float r, float g, float b);
		// defini�ao da componente difusa da luz
		void SetDifuseLightValue(float r, float g, float b);
		// defini�ao da componente especular da luz
		void SetSpecularLightValue(float r, float g, float b);

		// define a direc�ao da luz
		void SetLightDirection(float x, float y, float z);
		// define a posi�ao da luz
		void SetLightPosition(float x, float y, float z);
		// define as constantes de atenua�ao da luz
		void SetAttenuationValues(float constant, float linear, float quadratic);
		// define o valor de expoente para a luz conica
		void SetLightExponentVal(float exponet);
		// define o angulo de cutOff
		void SetLightCutOffAngle(float angle_degrees);
		// define o angulo de cutoff maior
		void SetLightOutCutOffAngle(float outer_angle_degrees);

		// Define valores da luz no shader
		void SetShaderLightValue(GLint shader_program);
		// actualiza os valores de estado da luz
		void UpdateShaderLightState(GLint shader_program);

	private:
		// variaveis internas
		kLIGHTTYPE light_type;	// indica o tipo de luz
		bool enable = false;	// indica se a luz est� activa
		// propriedades
		float ambient_light_value[3]{};		// cor da luz ambiente
		float difuse_light_value[3]{};		// valor da luz difusa
		float specular_light_value[3]{};	// valor da luz especular

		// coeficientes de atenua�ao, constante, linear e quadratico
		float constant = 0, linear = 0, quadratic = 0;

		// dire�ao e posi�ao da luz
		float light_position[3]{};		// posi�ao da luz
		float light_direction[3]{};		// dire�ao da luz

		// valor de cutOff para luz conica
		float exponent_val = 0;			// expoente para a luz conica
		float cutoff_angle = 0;			// angulo de cutOff
		float outr_cutoff_angle = 0;	// angulo maior de cutoff
	};
}

#endif