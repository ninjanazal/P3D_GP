#version 440 core

// uniforms
layout(location = 0) uniform mat4 _MVP;		// matriz mpv
layout(location = 1) uniform float _TIME;	// Valor do tempo
uniform bool _ENABLE_DEFORMATION;	// uniform que indica se a deforma��o est� activa

// Atributos
// objectivo
layout(location = 0) in vec3 vPosition;		// posi�ao dos vertices
layout(location = 1) in vec3 vNormals;		// normais dos vertices
layout(location = 2) in vec2 vTex_Coords;	// coordenadas de textura

// saida
// saida das normais
layout(location = 0) out vec3 v2f_Normals;	// valor das normais
layout(location = 1) out vec2 v2f_Tex_Coords;	// valor das coordenadas de textura

void main()
{
	// determina a posi�ao de clip dos vertices
	// vector de deforma�ao
	vec3 deformation_Vector = vec3(0.0f);
	
	// caso a deforma�ao esteja activa
	if(_ENABLE_DEFORMATION){
		// determina o vector de deforma�ao de acordo com as normais e o tempo
		deformation_Vector.x = sin(vPosition.y * 5 + _TIME * 2.0f) * 0.5f;
	}
	// define as posi�oes de clip dos vertices 
	gl_Position = _MVP * vec4(vPosition + deformation_Vector,1.0f);
	// passa para saida o valor das coordenadas de textura
	v2f_Normals = vNormals;	// guarda no valor de saida as normais
	v2f_Tex_Coords = vTex_Coords;	// guarda no valor de saida as coordenadas de textura
}