#pragma once
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
		Object(glm::vec3[], size_t);		// construtor da classe, para a criação de objectos directamente dos pontos definidos
		Object(const char*);		// overload do construtor para receber um caminho para o objecto

		~Object() { std::cout << "Objecto destruido" << std::endl; };	// destrutor da classe

		// funçoes do objecto
		// Funçao que valida o objecto
		bool Validate(void);
		
		// Buffers
		// Funçao para gerar e carregar buffers
		void LoadBuffers(void);

		// informaçao publica
		P3D::Material* object_material;	// material do objecto

		// getters
#pragma region Getters
		// getter para o vector de vertices
		std::vector<glm::vec3> GetVertexs(void) { return this->vertex; };
		// getter para o vector de normais
		std::vector<glm::vec3> GetNormals(void) { return this->normals; };
		// getter para as coordenadas de textura
		std::vector<glm::vec2> GetTexCoords(void) { return this->tex_coords; };
		// getter para o nome do objecto
		std::string GetObjName(void) { return this->xyz_file; };
#pragma endregion Getters

	private:
		std::string dir_path;	// caminho para o directorio do ficheiro
		std::string xyz_file;	// nome do ficheiro xyz

		std::vector<glm::vec3> vertex;		// vertices do objecto
		std::vector<glm::vec3> normals;		// normais dos vertices
		std::vector<glm::vec2> tex_coords;	// coordenadas de textura

		// render information
		GLuint VAO_name[1]{};	// nome atribuido ao VAO do objecto
		GLuint Buffers_names[BUFFER_COUNT]{};	// array de nome de buffers (VBO)
	};

	// construtor que recebe um vector com os vertices e a quantidade de vertices
	Object::Object(glm::vec3 vertexs[], size_t vertex_count)
	{
		// inicializa o material vazio
		object_material = new P3D::Material();

		// avalia se foram passados vertices
		if (static_cast<int>(vertex_count) == 0) return;

		// adiciona aos valores da classe a posiçao dos vertices
		for (int i = 0; i < static_cast<int>(vertex_count); i++)
			vertex.push_back(vertexs[i]);	// carrega para o vector de vertices os valores passados

		// imprime a quantidade de vertices carregados
		std::cout << "Carregados " << static_cast<int>(vertex_count) << " vertices!\n";
	}

	// construtor que recebe um path para dar load no obj
	Object::Object(const char* dir_)
	{
		// guarda o caminho para o directorio dos ficheiros
		this->dir_path = dir_;
		this->dir_path.push_back('\\');

		// mostra o directorio
		std::cout << this->dir_path << std::endl;

		char file_name[256];	// nome do ficheiro inserido
		// leitura do ficheiro .XYZ
		// requer o nome do ficheiro xyz
		std::cout << "Insert xyz file name: ";

		std::cin.ignore(); std::cin.clear();	// ingnora e limpa buffer de input actual
		std::cin.get(file_name, sizeof(file_name) / sizeof(file_name[0]));

		// adiciona o nome inserido ao caminho do ficheiro
		this->xyz_file = file_name;

		// mostra o caminho para o ficheiro
		std::cout << "xyz file path -> " << this->xyz_file << std::endl;

		// avalia se o caminho para o objecto é valido
		if (P3D::ConfirmFile((this->dir_path + this->xyz_file).c_str()))
		{
			// caso seja válido
			std::cout << "Start loading file...\n" << std::endl;

			// chama a leitura de dados do objecto do ficheiro, guarda a string retornada
			std::string load_obj_mat = P3D::LoadObjValues((this->dir_path + this->xyz_file).c_str(), vertex, normals, tex_coords);
			if (vertex.size() > 0 && normals.size() > 0 && tex_coords.size() > 0)
			{
				// indica a quantidade de vertices, normais e coordenadas de textura carregadas
				std::cout << "Loaded:\n\t->Vertex: " << vertex.size() << "\n\t->Normals: " << normals.size() <<
					"\n\t->Tex_Coords: " << tex_coords.size() << std::endl;

				// verifica se existe um material definido
				if (!load_obj_mat.empty())
				{
					std::cout << "Material file detected -> " << load_obj_mat << std::endl;
					// indica que é iniciado a leitura de dados do material
					std::cout << "Setting Material properties..." << std::endl;
					object_material = new P3D::Material(load_obj_mat.c_str(), dir_path.c_str());
				}
			}
		}
		else	// caso contrario, indica que nao foi possivel ler
			std::cout << "Failed to load File.\n";
	}

	// validate object
	bool Object::Validate(void)
	{
		// avalia se existem vertices no objecto
		return (vertex.size() > 0) ? true : false;
	}

	// Carrega buffers
	void Object::LoadBuffers(void)
	{
		// imprime que o carregamento para buffers de gpu é iniciado
		std::cout << "\n\n ----> Start Loading GPU buffers..." << std::endl;

		// sabendo que apenas será renderizado um objecto, será utilizado apenas 1 VAO
		// como tal, gera nome para o VAO do obj
		glGenVertexArrays(GLuint(1), this->VAO_name);
		
		// Bind ao VAO criado, nome alocado na VAO_name[0]. É activado o VAO ao dar bind
		glBindVertexArray(this->VAO_name[0]);

		// com o VAO definido e activo, carrega valor dos buffers
		// gerar nomes dos buffers, gera 3 buffers (posiçao, normal e tex coords)
		glGenBuffers(GLuint(BUFFER_COUNT), this->Buffers_names);

		// informa que os buffers vao ser carregados
		std::cout << "Passing data to GPU buffers..." << std::endl;

		// para cada um dos VBOs
		// vertices, inicia VBO, GL_ARRAY_BUFFER para atributos vertices com o nome atribuido
		glBindBuffer(GL_ARRAY_BUFFER, this->Buffers_names[0]);
		// atribui valor dos vertices para o VBO[0]
		glBufferStorage(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->vertex.size(), this->vertex.data(), 0);
		
		// normais, iniciar VBO, para atributos das normormais com o nome atribuido
		glBindBuffer(GL_ARRAY_BUFFER, this->Buffers_names[1]);
		// atribui valor das normais para o buffer vinculado
		glBufferStorage(GL_ARRAY_BUFFER, sizeof(glm::vec3) * this->normals.size(), this->normals.data(), 0);

		// tex_coords, iniciar VBO para atributos das coordenadas de textura
		glBindBuffer(GL_ARRAY_BUFFER, this->Buffers_names[2]);
		// atribui valor das coordenadas de textura para o buffer vinculado
		glBufferStorage(GL_ARRAY_BUFFER, sizeof(glm::vec2) * this->tex_coords.size(), this->tex_coords.data(), 0);

		// chama o bind da textura
		this->object_material->material_texture->LoadTextureBuffer();

		// indica que os buffers relacionado com o objecto estao carregados
		std::cout << "All Buffers Loaded!" << std::endl;
	}
}

