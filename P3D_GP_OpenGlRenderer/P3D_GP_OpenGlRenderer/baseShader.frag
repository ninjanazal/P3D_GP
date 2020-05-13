// fragment shader para RenderApp
#version 440 core
// uniforms
layout(location = 2) uniform sampler2D obj_texture;
layout(location = 3) uniform vec3 _VIEW_POS;	// posiçao da camera
layout(location = 4) uniform vec3 _VIEW_DIR;	// direçao da vista da camera

// propriedades do material
struct _MATERIAL{
	vec3 KA_AMBIENT;	// coeficiente de reflexao da luz ambient
	vec3 KD_DIFUSE;		// coeficiente de reflaxao da luz difusa
	vec3 KS_SPECULAR;	// coeficiente da luz especular
	float NS_SPECULAR;	// expoente especular
};
// uniform da estrutura material
uniform _MATERIAL MAT;

// propriedades da luz
struct _LIGHT{
	bool ENABLE;	// indica se a luz está activa
	vec3 COLOR;		// cor da luz
};


// entrada de valores vindos do vertex
layout(location = 0) in vec3 v2f_Normals;	// entrada dos valores das normais vindas do vertex
layout(location = 1) in vec2 v2f_Tex_Coords;	// entrada dos valores das coordenadass de textura

layout(location = 0)out vec4 fColor;	// cor de saida do fragmento

void main()
{
	// cor do fragmento de acordo com a textura
	vec4 tex_Color = texture(obj_texture,v2f_Tex_Coords);

	// debug normais com viewDir
	float dot_p = dot(v2f_Normals,_VIEW_DIR);
	// define a cor de saida igual á cor determinada para o fragmento de acordo com a imagem
	fColor = tex_Color;


	// ============== debug vars =============
	//fColor = tex_Color * dot_p;


	//fColor = normalize(abs(vec4(_VIEW_POS,1.0f)));

	// debug direcçao da camera
	//fColor = normalize(abs(vec4(_VIEW_DIR,1.0f)));
	// debug propriendades do material
	//fColor = normalize(abs(vec4(MAT.KS_SPECULAR,1.0f)));
	//fColor = tex_Color * normalize(abs(vec4(MAT.KA_AMBIENT,1.0f)));
	//fColor = normalize(abs(vec4(MAT.KS_SPECULAR,1.0f)));

	//fColor = normalize(abs(vec4(MAT.NS_SPECULAR,MAT.NS_SPECULAR,MAT.NS_SPECULAR,1.0f)));
}