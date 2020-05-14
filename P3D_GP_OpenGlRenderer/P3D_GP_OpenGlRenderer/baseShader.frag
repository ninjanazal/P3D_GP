// fragment shader para RenderApp
#version 440 core
// uniforms
// entrada de valores vindos do vertex
layout(location = 0) in vec3 v2f_Normals;	// entrada dos valores das normais vindas do vertex
layout(location = 1) in vec2 v2f_Tex_Coords;	// entrada dos valores das coordenadass de textura
layout(location = 2) uniform sampler2D obj_texture;	// textura do objecto
layout(location = 3) uniform vec3 _VIEW_POS;	// posiçao da camera
layout(location = 4) uniform vec3 _VIEW_DIR;	// direçao da vista da camera

// ================ material ====================
struct _MATERIAL{
	vec3 KA_AMBIENT;	// coeficiente de reflexao da luz ambient
	vec3 KD_DIFUSE;		// coeficiente de reflaxao da luz difusa
	vec3 KS_SPECULAR;	// coeficiente da luz especular
	float NS_SPECULAR;	// expoente especular
};
// uniform da estrutura material
uniform _MATERIAL MAT;

// =============== Luz ========================
// propriedades da ambiente
struct _AMBIENT_LIGHT{
	bool _ENABLE;	// indica se a luz está activa
	vec3 _COLOR;	// cor da luz
};
// uniform da luz ambiente
uniform _AMBIENT_LIGHT AMBIENTLIGHT;


// ======================== OUT =======================
// valor de saida do fragment
layout(location = 0)out vec4 fColor;	// cor de saida do fragmento

// declaraçao de funçoes
// Funçao retorna o valor de influencia da luz ambient
vec4 AmbientLightValue();

void main()
{
	// cor do fragmento de acordo com a textura
	vec4 tex_Color = texture(obj_texture,v2f_Tex_Coords);

	// define a cor ddo fragmento de acordo com a luz 
	fColor = (AmbientLightValue()) *  tex_Color;
}

// definiçao das funçoes
// calculo do valor da luz ambiente
vec4 AmbientLightValue(){
	return vec4(MAT.KA_AMBIENT * AMBIENTLIGHT._COLOR * ((AMBIENTLIGHT._ENABLE) ? 1.0f : 0.0f), 1.0f);
}
