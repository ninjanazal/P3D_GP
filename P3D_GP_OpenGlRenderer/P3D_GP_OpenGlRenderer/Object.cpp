#include "Object.h"

namespace P3D {
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


				// ao definir o objecto inicia a matriz de modelo, identidade
				this->model_matrix = glm::mat4(1.0f);

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
	void Object::LoadBuffers(void) {
		// imprime que o carregamento para buffers de gpu é iniciado
		std::cout << "\n\n=====> Start Loading GPU buffers..." << std::endl;

		// sabendo que apenas será renderizado um objecto, será utilizado apenas 1 VAO
		// como tal, gera nome para o VAO do obj
		glGenVertexArrays(GLuint(1), this->VAO_name);
		// Bind ao VAO criado, nome alocado na VAO_name[0]. É activado o VAO ao dar bind
		glBindVertexArray(this->VAO_name[0]);

		// com o VAO definido e activo, carrega valor dos buffers
		// gerar nomes dos buffers, gera 3 buffers (posiçao, normal e tex coords)
		glGenBuffers(BUFFER_COUNT, this->Buffers_names);


		// para cada um dos VBOs
		// vertices, inicia VBO, GL_ARRAY_BUFFER para atributos vertices com o nome atribuido
		glBindBuffer(GL_ARRAY_BUFFER, this->Buffers_names[0]);
		// atribui valor dos vertices para o VBO[0]
		glBufferStorage(GL_ARRAY_BUFFER, vertex.size() * 3 * sizeof(float), &vertex[0], 0);

		// normais, iniciar VBO, para atributos das normormais com o nome atribuido
		glBindBuffer(GL_ARRAY_BUFFER, this->Buffers_names[1]);
		// atribui valor das normais para o buffer vinculado
		glBufferStorage(GL_ARRAY_BUFFER, normals.size() * 3 * sizeof(float), &normals[0], 0);

		// tex_coords, iniciar VBO para atributos das coordenadas de textura
		glBindBuffer(GL_ARRAY_BUFFER, this->Buffers_names[2]);
		// atribui valor das coordenadas de textura para o buffer vinculado
		glBufferStorage(GL_ARRAY_BUFFER, tex_coords.size() * 2 * sizeof(float), &tex_coords[0], 0);

		// chama o bind da textura
		this->object_material->material_texture->LoadTextureBuffer();

		// indica que os buffers relacionado com o objecto estao carregados
		std::cout << "All Buffers Loaded!" << std::endl;
	}

	// Carrega Shaders
	bool Object::LoadShaders(void)
	{
		// indica que começou a carregar os ficheiros de shader
		std::cout << "\n\n=====> Start loading Shader Programs..." << std::endl;

		// inicia o programa shader (retornando "nome")
		shader_program = glCreateProgram();

		// inicia a definiçao de cada um dos shaders
		//**************** vertex shader
		if (!LoadVertexShader())
			return false;	// caso nao tenha carregado o vertex shader

		// ************* Fragment Shader
		if (!LoadFragmentShader())
			return false;	// caso nao tenha carregado o fragment shader

		// linka o programa com os shader definidos
		glLinkProgram(shader_program);
		// verifica se a linkagem correu com sucesso
		GLint link;
		// guarda o resultado do request
		glGetProgramiv(shader_program, GL_LINK_STATUS, &link);
		// verifica o resultado
		if (!link) {
			// imprime o log do erro da linkagem
			// tamanho do log
			GLint leng;
			// guarda o tamanho retornado pelo request
			glGetProgramiv(shader_program, GL_INFO_LOG_LENGTH, &leng);
			// array de log
			GLchar* log = new GLchar[leng + 1];
			// request que retorna o log
			glGetProgramInfoLog(shader_program, leng, &leng, log);
			// imprime o resultado na consola
			std::cout << "Linking Error: " << log << std::endl;
			// apaga a memoria alocada
			delete[] log;

			// elimina os shaders criados
			glDeleteShader(vertex_shader_name);		// vertex shader
			glDeleteShader(fragment_shader_name);	// fragment shader

			// pausa o sistema
			system("pause");

			// retorna
			return false;
		}

		// informa que a linkagem ocorreu com sucesso
		std::cout << "Shader Program Linked Successfully!" << std::endl;

		// indica o uso do programa pelo GL
		glUseProgram(shader_program);
		// indica que o novo programa está a ser utilizado
		std::cout << "\n->Shader Program in Use!" << std::endl;

		// retorna que o carregamento foi feito com sucesso
		return true;
	}

	// liga atributos ao shader
	void Object::ConnectShaderValues(void) {
		// indica que é iniciado a vinculaçao dos dados
		std::cout << "Connecting buffer values to shader properties!" << std::endl;

		// existindo apenas um vao, nao é necessario vincular esse vai, no entnao pode ser feito
		glBindVertexArray(this->VAO_name[0]);

		// vincula o bvo dos vertice
		glBindBuffer(GL_ARRAY_BUFFER, Buffers_names[0]);
		// vertices
		// vincula o vbo 0 , para atribuiçao das posiçoes de vertices
		// obtem a localizaçao do atributo "vPosition" no programa
		GLint vPosition_location =
			glGetProgramResourceLocation(shader_program, GL_PROGRAM_INPUT, "vPosition");
		// com a poisçao do atributo, é definido como os valores sao interpretados
		glVertexAttribPointer(vPosition_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		// activa o atributo
		glEnableVertexAttribArray(vPosition_location);

		// normais
		// vincula o bvo das normais
		glBindBuffer(GL_ARRAY_BUFFER, Buffers_names[1]);

		// vincula o vbo 1, para atribuiçao dos valores de normais
		// obtem a localozaçao do atributo "vNormals" no programa
		GLint vNormals_location =
			glGetProgramResourceLocation(shader_program, GL_PROGRAM_INPUT, "vNormals");
		// com a +posiçao do atributo, é definido como os valores sao interpretados
		glVertexAttribPointer(vNormals_location, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
		// activa o atributo
		glEnableVertexAttribArray(vNormals_location);


		// coordenadas de textura
		// vincula o bvo das normais
		glBindBuffer(GL_ARRAY_BUFFER, Buffers_names[2]);

		// vincula o vbo 2, para atribuiçao das coordenadas de textura
		// obtem a localizaçao do atributo "vTex_Coords" no programa
		GLint vTex_Coords_location =
			glGetProgramResourceLocation(shader_program, GL_PROGRAM_INPUT, "vTex_Coords");
		// com a posiçao do atributo, é definido como os valores sao interpretados
		glVertexAttribPointer(vTex_Coords_location, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
		// activa o atributo
		glEnableVertexAttribArray(vTex_Coords_location);

		// TODO
		// atribuir textura 
		this->object_material->material_texture->ConnectTextureShaderValue(this->shader_program);

		// indica que os atributos foram definidos com sucesso
		std::cout << "Buffers Connected!" << std::endl;
	}

	// vincula o vao do obj
	void Object::Drawobj(void) {
		// vincula o vao do objecto
		glBindVertexArray(this->VAO_name[0]);
		// vincula o buffer de vertices
		glBindBuffer(GL_ARRAY_BUFFER, this->Buffers_names[0]);

		// envia o comando de desenho das primitivas utilizando o vao vinculado
		glDrawArrays(GL_TRIANGLES, 0, this->vertex.size());
	}

#pragma region PrivateMethods
	// Metodos privados
	// carrega o vertex shader
	bool Object::LoadVertexShader(void) {
		// cria um vertex shader e retorna o seu nome
		vertex_shader_name = glCreateShader(GL_VERTEX_SHADER);
		// efectua a leitura dos dados presentes no shader, guarda o shader numa var temp
		std::string shader_data_string = P3D::LoadShader("baseShader.vert");
		// criado um array temporario para conversao de tipos de dados
		const GLchar* shader_data = shader_data_string.c_str();

		// verifica se foram retornados dados do shader
		if (shader_data_string.empty()) {
			// informa que nao foram retornados dados do shader
			std::cout << "Failed do return Vertex shader data!" << std::endl;
			// elimina o shader criado
			glDeleteShader(vertex_shader_name);
			glDeleteShader(fragment_shader_name);
			// retorna
			return false;
		}
		// carrega o codigo do shader para memoria grafica
		// indica o nome do shader, a quantidade de elementos , a referencia para o codigo 
		// null para array dos comprimentos da string
		glShaderSource(vertex_shader_name, 1, &shader_data, NULL);
		// compila o shader
		glCompileShader(vertex_shader_name);
		// verifica a compilaçao do shader
		GLint compiled;	// int para guardar o resultado do request
		glGetShaderiv(vertex_shader_name, GL_COMPILE_STATUS, &compiled);
		// verifica se o shader foi compilado
		if (!compiled)
		{
			// imprime se o shader foi compilado com sucesso
			std::cout << "Shader Failed to Compile!" << std::endl;
			// para imprimir o erro
			// determina o tamanho 
			GLsizei leng;
			glGetShaderiv(vertex_shader_name, GL_INFO_LOG_LENGTH, &leng);

			// guarda o log do erro
			GLchar* log = new GLchar[leng + GLint(1)];
			glGetShaderInfoLog(vertex_shader_name, leng, &leng, log);
			// imprime o erro
			std::cout << "Error: " << log << std::endl;
			// pausa o sistema
			system("pause");

			// ao falhar elimina o shader
			glDeleteShader(vertex_shader_name);
			glDeleteShader(fragment_shader_name);
			return false;	// retorna que o shader falhou ao ser compilado
		}
		// informa que o shader foi compilado com sucesso
		std::cout << "Vertex Shader Compiled!" << std::endl;

		// Estando compilado com sucesso, adiciona o shader ao programa
		glAttachShader(shader_program, vertex_shader_name);

		//// elimina o array temporario de dados e a string
		//delete shader_data;

		// informa que o shader foi carregado correctamente
		std::cout << "Vertex Shader loaded Successfully!" << std::endl;
		return true;
	}

	// carrega o Fragment shader
	bool Object::LoadFragmentShader(void) {
		// cria um fragment shader e retorna o seu nome
		fragment_shader_name = glCreateShader(GL_FRAGMENT_SHADER);
		// efectua a leitura dos dados presentes no shader, guarda o shader numa var temp
		std::string shader_data_string = P3D::LoadShader("baseShader.frag").c_str();
		// criado um array temporario para conversao de tipos de dados
		const GLchar* shader_data = shader_data_string.c_str();

		// verifica se foram retornados dados do shader
		if (shader_data_string.empty()) {
			// informa que nao foram retornados dados do shader
			std::cout << "Failed to return Fragment shader data|" << std::endl;
			// elimina o shader criado
			glDeleteShader(vertex_shader_name);
			glDeleteShader(fragment_shader_name);
			// retorna
			return false;
		}
		// carrega o codigo do shader para memoria grafica
		glShaderSource(fragment_shader_name, 1, &shader_data, NULL);
		// compila o shader
		glCompileShader(fragment_shader_name);
		// verifica a compilaçao do shader
		GLint compiled;	// int para guardar o resultado do request
		glGetShaderiv(fragment_shader_name, GL_COMPILE_STATUS, &compiled);
		// verifica se o shader foi compilado
		if (!compiled) {
			// imprime que o shader nao foi compilado com sucesso
			std::cout << "Shader Failed to Compile!" << std::endl;

			// para imprimir o erro
			// determina o tamanho 
			GLsizei leng;
			glGetShaderiv(vertex_shader_name, GL_INFO_LOG_LENGTH, &leng);

			// guarda o log do erro
			GLchar* log = new GLchar[leng + GLint(1)];
			glGetShaderInfoLog(vertex_shader_name, leng, &leng, log);
			// imprime o erro
			std::cout << "Error: " << log << std::endl;
			// pausa o sistema
			system("pause");

			// ao flahar elimina o shader
			glDeleteShader(vertex_shader_name);
			glDeleteShader(fragment_shader_name);
			// retorna que o falhou
			return false;
		}
		// informa que o shader foi compilado com sucesso
		std::cout << "Fragment shader Compiled!" << std::endl;

		// estando compilado com sucesso, adiciona o shader ao programa
		glAttachShader(shader_program, fragment_shader_name);
		// elimina o array temporario de dados
		//delete[] shader_data;

		// informa que o shader foi carregado correctamente
		std::cout << "Fragment Shader loaded Successfully!" << std::endl;
	}

#pragma endregion
}