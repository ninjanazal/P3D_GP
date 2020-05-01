#pragma once
#include "Material.h" // include de materiais

namespace P3D
{
	// class de objecto, responsavel por armazenar informação relacionada com
	// o objecto
	class Object
	{
	public:
		// csontrutores
		Object(glm::vec3[], size_t);		// construtor da classe, para a criação de objectos directamente dos pontos definidos
		Object(const char*);		// overload do construtor para receber um caminho para o objecto

		~Object() { std::cout << "Objecto destruido" << std::endl; };	// destrutor da classe

		// getters
#pragma region Getters
		// getter para o vector de vertices
		std::vector<glm::vec3> GetVertexs(void) { return this->vertex; };
		// getter para o vector de normais
		std::vector<glm::vec3> GetNormals(void) { return this->normals; };
		// getter para as coordenadas de textura
		std::vector<glm::vec2> GetTexCoords(void) { return this->tex_coords; };

#pragma endregion Getters

	private:
		std::string dir_path;	// caminho para o directorio do ficheiro
		std::string xyz_file;	// nome do ficheiro xyz
				
		std::vector<glm::vec3> vertex;		// vertices do objecto
		std::vector<glm::vec3> normals;		// normais dos vertices
		std::vector<glm::vec2> tex_coords;	// coordenadas de textura

		Material *object_material;	// material do objecto
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

		// adiciona o caminho para o directorio ao caminho do file
		this->xyz_file = this->dir_path;

		// mostra o directorio
		std::cout << this->dir_path << std::endl;

		char file_name[256];	// nome do ficheiro inserido
		// leitura do ficheiro .XYZ
		// requer o nome do ficheiro xyz
		std::cout << "Insert xyz file name: ";

		std::cin.ignore(); std::cin.clear();	// ingnora e limpa buffer de input actual
		std::cin.get(file_name, sizeof(file_name) / sizeof(file_name[0]));

		// adiciona o nome inserido ao caminho do ficheiro
		this->xyz_file += file_name;

		// mostra o caminho para o ficheiro
		std::cout << "xyz file path -> " << this->xyz_file << std::endl;

		// avalia se o caminho para o objecto é valido
		if (P3D::ConfirmFile(xyz_file.c_str()))
		{
			// caso seja válido
			std::cout << "Start loading file...\n" << std::endl;

			// chama a leitura de dados do objecto do ficheiro, guarda a string retornada
			std::string load_obj_mat = P3D::LoadObjValues(xyz_file.c_str(), vertex, normals, tex_coords);
			if (vertex.size() >0 && normals.size() > 0 && tex_coords.size() > 0)
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
}

