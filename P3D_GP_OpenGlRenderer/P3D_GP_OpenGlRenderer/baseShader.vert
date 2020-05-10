#version 440 core
// uniforms
layout(location = 0) uniform mat4 _MVP;		// matriz mpv
layout(location = 1) uniform float _TIME;	// Valor do tempo

// Atributos
// objectivo
layout(location = 0) in vec3 vPosition;		// posiçao dos vertices
layout(location = 1) in vec3 vNormals;		// normais dos vertices
layout(location = 2) in vec2 vTex_Coords;	// coordenadas de textura

// saida
// saida das normais
layout(location = 0) out vec3 v2f_Normals;	// valor das normais
layout(location = 1) out vec2 v2f_Tex_Coords;	// valor das coordenadas de textura

void main()
{
	// determina a posiçao de clip dos vertices
	gl_Position = _MVP * vec4(vPosition,1.0f);
	// passa para saida o valor das coordenadas de textura
	v2f_Normals = vNormals;	// guarda no valor de saida as normais
	v2f_Tex_Coords = vTex_Coords;	// guarda no valor de saida as coordenadas de textura
}