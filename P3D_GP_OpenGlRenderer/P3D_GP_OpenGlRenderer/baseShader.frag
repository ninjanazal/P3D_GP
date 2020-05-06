// fragment shader para RenderApp
#version 440 core
// uniforms
layout(location = 2) uniform sampler2D obj_texture;

// entrada de valores vindos do vertex
layout(location = 0) in vec3 v2f_Normals;	// entrada dos valores das normais vindas do vertex
layout(location = 1) in vec2 v2f_Tex_Coords;	// entrada dos valores das coordenadass de textura

layout(location = 0)out vec4 fColor;	// cor de saida do fragmento

void main()
{
	// cor do fragmento de acordo com a textura
	vec4 tex_Color = texture(obj_texture,v2f_Tex_Coords);
	// define a cor de saida igual á cor determinada para o fragmento de acordo com a imagem
	fColor = tex_Color;
}