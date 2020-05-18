#version 440 core

// uniforms
uniform mat4 _MVP;		// matriz mpv
uniform mat4 _MODEL;	// amtriz de modelo
layout(location = 1) uniform float _TIME;	// Valor do tempo
uniform bool _ENABLE_DEFORMATION;	// uniform que indica se a deformação está activa

// Atributos
// objectivo
layout(location = 0) in vec3 vPosition;		// posiçao dos vertices
layout(location = 1) in vec3 vNormals;		// normais dos vertices
layout(location = 2) in vec2 vTex_Coords;	// coordenadas de textura

// saida
// saida das normais
layout(location = 0) out vec4 v2f_Positions;	// valor das pos dos vertices
layout(location = 1) out vec4 v2f_Normals;		// valor das normais
layout(location = 2) out vec2 v2f_Tex_Coords;	// valor das coordenadas de textura

void main()
{
	// determina a posiçao de clip dos vertices
	// vector de deformaçao
	vec3 deformation_Vector = vec3(0.0f);
	
	// caso a deformaçao esteja activa
	if(_ENABLE_DEFORMATION){
		// determina o vector de deformaçao de acordo com as normais e o tempo
		deformation_Vector.x = sin(vPosition.y * 5 + _TIME * 2.0f) * 0.5f;
	}
	// define as posiçoes de clip dos vertices 
	gl_Position = _MVP * vec4(vPosition + deformation_Vector,1.0f);
	// passa para saida o valor das coordenadas de textura
	v2f_Positions = _MODEL * vec4(vPosition + deformation_Vector,1.0f);	// guarda no valor de saida as posiçoes transformadas para espaço mundo
	v2f_Normals = _MODEL * vec4(vNormals,1.0f);	// guarda no valor de saida as normais transformadas para espaço do mundo
	v2f_Tex_Coords = vTex_Coords;	// guarda no valor de saida as coordenadas de textura
}