#pragma once
// sao incluidas e definidas todas as librarias externas visto que todo o programa dependerá 
// maioritariamente, occorendo aqui grande parte da transformaçao do mesmo
#pragma comment(lib, "glew32s.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")

#include <iostream>
#include <vector>

#define GLEW_STATIC
#include <GL\glew.h>

#include <GLFW\glfw3.h>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...
#include <glm/gtc/matrix_transform.hpp> // translate, rotate, scale, perspective, ...
#include <glm/gtc/type_ptr.hpp> // value_ptr

namespace P3D
{
	// class de objecto, responsavel por armazenar informação relacionada com
	// o objecto
	class Object
	{
	public:
		// construtor da classe, para a criação de objectos directamente dos pontos definidos
		Object(glm::vec3[], size_t);
		// overload do construtor para receber um caminho para o objecto
		Object(const char*);
		~Object() { std::cout << "Objecto destruido" << std::endl; };	// destrutor da classe
		
		// getters
#pragma region Getters
		// getter para o vector de vertices
		std::vector<glm::vec3> GetVertexs(void) { return this->vertex; };	
		// getter para o vector de normais
		std::vector<glm::vec3> GetNormals() { return this->normals; };
		// getter para as coordenadas de textura
		std::vector<glm::vec2> GetTexCoords() { return this->tex_coords; };
#pragma endregion Getters

	private:
		std::vector<glm::vec3> vertex;		// vertices do objecto
		std::vector<glm::vec3> normals;		// normais dos vertices
		std::vector<glm::vec2> tex_coords;	// coordenadas de textura
	};

	// construtor que recebe um vector com os vertices e a quantidade de vertices
	Object::Object(glm::vec3 vertexs[], size_t vertex_count)
	{
		// avalia se foram passados vertices
		if (vertex_count == 0) return;

		// adiciona aos valores da classe a posiçao dos vertices
		for (int i = 0; i < vertex_count; i++)
			vertex.push_back(vertexs[i]);	// carrega para o vector de vertices os valores passados

		// imprime a quantidade de vertices carregados
		std::cout << "Carregados " << vertex_count << " vertices!\n";
	}
	// construtor que recebe um path para dar load no obj
	Object::Object(const char* obj_path) {

	}


}

