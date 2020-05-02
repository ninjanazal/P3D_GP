#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "FileFuncs.h"

namespace P3D
{
#pragma region AuxFuncs
	// informaçao sobre funçoes presentes 
	std::string LoadFile(const char*);		// leitura de ficheiro nao binario
	std::string LoadBinFile(const char*);	// leitura de ficheiro binario

#pragma endregion AuxFuncs

	// confirmação da existencia do ficheiro
	bool ConfirmFile(const char* kFile_path)
	{
		//Abre o ficheiro para leitura, caso consiga, o ficheiro existe
		std::fstream test_load(kFile_path, std::ios::in);

		// determina se o ficheiro consegue ser aberto
		std::cout << "Exists? : " << test_load.is_open() << std::endl;
		// retorna o valor de confirmaçao
		if (test_load.is_open())
		{
			// fecha o ficheiro
			test_load.close();
			return(true);
		}
		else {	// caso nao consia abrir
			test_load.close();	// fecha o ficheiro
			return(false);
		}
	}

	// carrega valores do objecto a partir do ficheiro xyz
	std::string LoadObjValues(const char* file_path, std::vector<glm::vec3>& vert,
		std::vector<glm::vec3>& norm, std::vector<glm::vec2>& tex_coord)
	{
		// limpa os vectores de vertices, normais e coordenadas de textura
		vert.clear(); norm.clear(); tex_coord.clear();

		std::string xyz_file = LoadFile(file_path);// carrega a informaçao do ficheiro para string
		std::string material_found;		// material definido no ficheiro

		// determina se foi retornado valores 
		if (xyz_file.empty())
		{
			// se caso nao tenha retornado dados, indica que falhou a leitura
			std::cout << "Failed to read file!" << std::endl;
		}
		else
		{
			// caso tenha retornado dados			
			std::istringstream string_stream(xyz_file); // stream de leitura
			char read_buffer[256];	// buffer de leitura de linha
			// vars  para leitura de valores de vertices, normais e tex_Coords
			float temp_x, temp_y, temp_z;


			// inicia a extraçao dos dados
			std::cout << "|--> Starting data object extraction..." << std::endl;

			// precorre linha a linha uzando um stream
			while (true)
			{
				// passa a palavra actual para o buffer de leitura
				string_stream >> read_buffer;

				// avalia se checou ao final do ficheiro
				if (string_stream.eof())
					break;	// salta fora do loop de leitura

				// para cada linha, avalia o tipo de dados
				// determina que tipo de informaçao contida na linha
				if (std::strcmp(read_buffer, "mtllib") == 0)	// definiçao de material
				{
					// nome do material encontrado
					string_stream >> material_found;	// nome do ficheiro é guardado					
					// indica que existe um material definido
					std::cout << "Material found: " << material_found << std::endl;;
				}
				else if (std::strcmp(read_buffer, "v") == 0)
				{
					// caso inicie por 'v' indica a leitura de vertices
					// extrai valores para variaveis temporarias
					string_stream >> temp_x >> temp_y >> temp_z;
					// com os valores extraidos sao adicionados ao vector de vetores
					vert.push_back(glm::vec3(temp_x, temp_y, temp_z));
				}
				else if (std::strcmp(read_buffer, "vt") == 0)
				{
					// caso inicie por "vt", inicia a leitura das coordenadas de textura
					// extrai valores para variaveis temporariasa
					string_stream >> temp_x >> temp_y;
					// com os valores extraidos, adiciona-se ao vector de coordenadas de textura
					tex_coord.push_back(glm::vec2(temp_x, temp_y));
				}
				else if (std::strcmp(read_buffer, "vn") == 0)
				{
					// caso inicie por "vn", inicia a leitura do valor de normais
					// extrai valores para variaveis temporarias
					string_stream >> temp_x >> temp_y >> temp_z;
					// com valores extraidos, adiciona-se ao vector de normais
					norm.push_back(glm::vec3(temp_x, temp_y, temp_z));
				}
			}

			// returna se encontrou um material, a variavel vai vazia caso nao exista
			// material definido
			return material_found;

		}
	}


	std::string LoadObjMaterialValues(const char* file_path, glm::vec3(&coef)[3], float& spec_exp)
	{
		// define uma string com toda a informaçao presente no ficheiro
		std::string mtl_file = LoadFile(file_path);
		std::string texture_found;	// nome da textura encontrada

		if (mtl_file.empty())
			// indica que falhou a leitura do ficheiro
			std::cout << "Failed to read file" << std::endl;
		else
		{
			// caso tenha retornado dados
			std::istringstream string_stream(mtl_file);	// stream de leitura
			char read_buffer[256];	// buffer de leitura
			// variaveis temporarias de leitura para valores presentes
			float temp_x, temp_y, temp_z;

			// inicia a extraçao de dados
			std::cout << "|--> Start material data extraction..." << std::endl;

			// precorre linha usando stream de leitura
			while (true)
			{
				// passa a palavra actual para o buffer de leitura
				string_stream >> read_buffer;

				// avalia o final da stream
				if (string_stream.eof())
					break;	// salta o ciclo assim que atingir o final do ficheiro

				// para cada linha avalia o tipo de dados
				// determina o tipo de informaçao representado na linha					
				if (std::strcmp(read_buffer, "Ka") == 0)
				{
					// caso inicie por "ka", inicia a leitura do coeficiente de reflexao
					// de luz ambiente, coef[0]
					string_stream >> temp_x >> temp_y >> temp_z;
					// com valores extraidos, adiciona ao array de coeficientes na posiçao 0
					coef[0] = glm::vec3(temp_x, temp_y, temp_z);
				}
				else if (std::strcmp(read_buffer, "Kd") == 0)
				{
					// caso inicie por "kd", inicia a leitura de coeficiente de reflexao
					// de luz difusa, coef[1]
					string_stream >> temp_x >> temp_y >> temp_z;
					// com os valores extraidos, adiciona ao array de coeficientes na posiçao 1
					coef[1] = glm::vec3(temp_x, temp_y, temp_z);
				}
				else if (std::strcmp(read_buffer, "Ks") == 0)
				{
					// caso inicie por "ks", inicia a leitura de coeficiente de reflexao
					// de luz especular
					string_stream >> temp_x >> temp_y >> temp_z;
					// com os valores extraidos, adiciona ao array de coeficientes na posiçao 2
					coef[2] = glm::vec3(temp_x, temp_y, temp_z);
				}
				else if (std::strcmp(read_buffer, "Ns") == 0)
				{
					// caso inicie por "ns", inicia a leitura do expoente especular
					string_stream >> spec_exp;
				}
				else if (std::strcmp(read_buffer, "map") == 0)
				{
					// caso inicie por "map", guarda o nome do ficheiro de textura
					string_stream >> texture_found;
					// indica que existe uma textura
					std::cout << "Texture Map found -> " << texture_found << std::endl;
				}
				else
					// para os valores restantes de informaçao sao ignorados
					string_stream.getline(read_buffer, 256);
			}
		}

		// retorna se encontrou uma textura, a variavel retorna vazia caso nao
		// exista textura definida
		return texture_found;
	}

	// funçoes axiliariares
#pragma region Helpers
	// funçao auxiliar para carregar ficheiro nao binario
	std::string LoadFile(const char* file_path)
	{
		std::string file_data;	// informaçao do ficheiro

		// abre o ficheiro para leitura, anteriormente confirmado, coloca o ponteiro no fim do ficheiro
		std::fstream file_load_stream(file_path, std::ios::in | std::ifstream::ate);

		// confirma se o ficheiro foi abert
		if (file_load_stream.is_open())
		{
			// guarda o tamanho do ficheiro em bits
			size_t file_size = file_load_stream.tellg();
			// coloca o leitor de volta ao inicio do ficheiro
			file_load_stream.seekg(0, std::ios::beg);

			// cria espaço em memoria para os dados
			char* data_to = new char[file_size + size_t(1)]{};
			file_load_stream.read(data_to, file_size);	// lê para tempArray os dados do ficheiro

			// marca o final da string 
			data_to[file_size] = 0;
			// guarda os dados lidos na string
			file_data = data_to;
			// elimina o tempArray
			delete[] data_to;

			// imprime que o ficheiro foi carregado com sucesso
			std::cout << "-> File loaded to mem..." << std::endl;
		}
		// fecha o ficheiro de leitura
		file_load_stream.close();
		// retorna a informaçao carregada do ficheiro
		return file_data;
	}

	// funçao auxiliar para carregar ficheiros binarios
	std::string LoadBinFile(const char* file_path)
	{
		std::string tga_file_data;	// informaçao do ficheiro bin

		// abre o ficheiro para leitura, confirmado anteriormente, coloco o ponteiro no fim do ficheiro
		std::fstream file_load_bin_stream(file_path, std::ios::in | std::ios::binary | std::ios::ate);

		// confirma se o ficheiro foi aberto
		if (file_load_bin_stream.is_open())
		{
			// guarda o tamanho do ficheiro em bits
			size_t file_size = file_load_bin_stream.tellg();
			// coloca o ponteiro de leitura no inicio da stream
			file_load_bin_stream.seekg(0, std::ios::beg);

			// cria espaço em memoria para os dados
			char* data_to = new char[file_size + size_t(1)]{};
			file_load_bin_stream.read(data_to, file_size);	// lê para temArray os dados do ficheiro

			// marca o final da string de leitura
			data_to[file_size] = 0;
			// guarda dados  lidos em string
			tga_file_data = data_to;
			// liberta a memoria alocada
			delete[] data_to;

			// imprime que o ficheiro foi carregado com sucesso
			std::cout << "-> File loaded to mem..." << std::endl;
		}
		// fecha o ficheiro de leitura
		file_load_bin_stream.close();
		// retorna a informaçao carregada do ficheiro
		return tga_file_data;
	}
#pragma endregion Helpers
}