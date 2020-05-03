#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <glm/glm.hpp> // vec3, vec4, ivec4, mat4, ...


namespace P3D
{
	// Funçao que avalia a existencia do ficheiro
	bool ConfirmFile(const char*);
	// Funçao de leitura de dados para estruturas internas do objeto, retorna se existe material definido
	std::string LoadObjValues(const char* file_path, std::vector<glm::vec3>&vert, std::vector<glm::vec3>&norm, std::vector<glm::vec2>&tex_coord);
	// Funçao de leitura de dados para estruturas internas do materias, retorna o nome da imagem de textura se definida
	std::string LoadObjMaterialValues(const char* file_path, glm::vec3 (&coef)[3], float&specular);
	// Funçao de leitura de dados de textura (.tga)
	void LoadTextureValues(const char* file_path);

	// shader
	// Funçao de leitura de ficheiro binario
	std::string LoadShader(const char* file_path);
}