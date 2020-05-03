// fragment shader para RenderApp
#version 440 core

// entrada de valores vindos do vertex
layout(location = 0) in vec3 v2f_Normals;	// entrada dos valores das normais vindas do vertex
layout(location = 1) in vec2 v2f_Tex_Coords;	// entrada dos valores das coordenadass de textura

layout(location = 0)out vec4 fColor;	// cor de saida do fragmento

void main()
{
	// coloca todos os fragmentos com a cor branca
	fColor = vec4(1.9f,1.0f,1.0f,1.0f);
}