#ifndef LIGHT_H
#define LIGHT_H

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

		// funçoes para a definiçao da luz
		void EnableLight();
		// imprime os valores da luz
		void DisplayLightInfo();

		// definiçao da cor da luz
		void SetLightValue(float r, float g, float b);

		// Define valores da luz no shader
		void SetShaderLightValue(GLint shader_program);
		// actualiza os valores de estado da luz
		void UpdateShaderLightState(GLint shader_program);
	private:
		// variaveis internas
		kLIGHTTYPE light_type;	// indica o tipo de luz
		float light_value[3]{};		// cor da luz
		bool enable = false;	// indica se a luz está activa

	};
}

#endif