#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h" // include de materiais

namespace P3D
{
	// define o numero de buffers
#define BUFFER_COUNT 3	

	// class de objecto, responsavel por armazenar informação relacionada com
	// o objecto
	class Object
	{
	public:
		// csontrutores
		Object(const char*);		// overload do construtor para receber um caminho para o objecto
		~Object() { std::cout << "Objecto destruido" << std::endl; };	// destrutor da classe


		// informaçao publica
		P3D::Material* object_material;	// material do objecto


	   // funçoes do objecto
	   // Funçao que valida o objecto
		bool Validate(void);

		// Buffers
		// Funçao para gerar e carregar buffers
		void LoadBuffers(void);

		// Shader
		// Funçao para carregar Shaders
		bool LoadShaders(void);
		// Função para atribuir valores ao shader
		void ConnectShaderValues(void);

		// desenho
		void Drawobj(void);
		// getters
#pragma region Getters
	// getter para o nome do objecto
		std::string GetObjName(void) { return xyz_file; };
		// getter para o nome do programa shader
		GLuint GetShaderProgram(void) { return shader_program; };
		// getter para a matriz de modelo
		glm::mat4 GetModelMat(void) { return P3D::Object::model_matrix; };
#pragma endregion Getters

	private:
		std::string dir_path;	// caminho para o directorio do ficheiro
		std::string xyz_file;	// nome do ficheiro xyz

		std::vector<glm::vec3> vertex;		// vertices do objecto
		std::vector<glm::vec3> normals;		// normais dos vertices
		std::vector<glm::vec2> tex_coords;	// coordenadas de textura


		// matriz de modelo
		glm::mat4 model_matrix;	// matriz de modelo

		// render information
		GLuint VAO_name[1]{};	// nome atribuido ao VAO do objecto
		GLuint Buffers_names[BUFFER_COUNT]{};	// array de nome de buffers (VBO)
		// vertex -> 0 normals -> 1, tex_coord -> 2

		// shader vars
		GLuint shader_program = 0, vertex_shader_name = 0, fragment_shader_name = 0;	// nome do programa shader

		// private Funcs
		// carrega o vertex Shader
		bool LoadVertexShader(void);
		// carrega o Fragment Shader
		bool LoadFragmentShader(void);
	};
}
#endif