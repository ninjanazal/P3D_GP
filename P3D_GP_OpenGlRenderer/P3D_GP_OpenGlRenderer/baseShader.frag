// fragment shader para RenderApp
#version 440 core
// entrada de valores vindos do vertex
layout(location = 0) in vec4 v2f_Positions;	// entrada dos valores das posiçoes dos vertices vindas do vertex
layout(location = 1) in vec4 v2f_Normals;	// entrada dos valores das normais vindas do vertex
layout(location = 2) in vec2 v2f_Tex_Coords;	// entrada dos valores das coordenadass de textura

// uniforms
uniform mat4 _MODEL;	// amtriz de modelo

uniform sampler2D obj_texture;	// textura do objecto
uniform vec3 _VIEW_POS;	// posiçao da camera

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
// +++++++++++++ propriedades da luz ambiente ++++++++++++++++++++++++
struct _AMBIENT_LIGHT{
	bool _ENABLE;	// indica se a luz está activa
	vec3 _COLOR;	// cor da luz
};
// uniform da luz ambiente
uniform _AMBIENT_LIGHT AMBIENTLIGHT;

//+++++++++++++++ propriedade de luz direcional +++++++++++++++++++++
struct _DIRECTIONAL_LIGHT{
	bool _ENABLE;			// indica se a luz está activa
	vec3 _DIRECTION;		// indica a direcçao da luz

	vec3 _AMBIENT_COMP;		// compornente de luz ambiente
	vec3 _DIFFUSE_COMP;		// componente de luz difusa
	vec3 _SPECULAR_COMP;	// componente de luz especular
};
// uniform da luz direcional
uniform _DIRECTIONAL_LIGHT DIRECTIONALLIGHT;

// +++++++++++++++ propriedades da luz pontual +++++++++++++++++++++++
struct _POINT_LIGHT{
	bool _ENABLE;			// indica se a luz está activa
	vec3 _POSITION;			// indica a posiçao da luz

	vec3 _AMBIENT_COMP;		// compornente de luz ambiente
	vec3 _DIFFUSE_COMP;		// componente de luz difusa
	vec3 _SPECULAR_COMP;	// componente de luz especular

	float _CONSTANT_VAL;	// coeficiente de atenuaçao constante
	float _LINEAR_VAL;		// coeficiente de atenuaçao linear
	float _QUADRATIC_VAL;	// coeficiente de atenuaçao quadratica
};
// Uniform da luz pontual
uniform _POINT_LIGHT POINTLIGHT;

// +++++++++++++++ propriedades da luz pontual +++++++++++++++++++++++
struct _SPOT_LIGHT{
	bool _ENABLE;			// indica se a luz está activa
	vec3 _POSITION;			// indica a posiçao da luz
	vec3 _DIRECTION;		// indica a direçao da luz

	vec3 _AMBIENT_COMP;		// compornente de luz ambiente
	vec3 _DIFFUSE_COMP;		// componente de luz difusa
	vec3 _SPECULAR_COMP;	// componente de luz especular

	float _CONSTANT_VAL;	// coeficiente de atenuaçao constante
	float _LINEAR_VAL;		// coeficiente de atenuaçao linear
	float _QUADRATIC_VAL;	// coeficiente de atenuaçao quadratica

	float _EXPONENT_VAL;	// valor exponencial da luz
	float _CUTOFF_ANGLE;	// angulo de cutOff da luz conica
};
// Uniform da luz pontual
uniform _SPOT_LIGHT SPOTLIGHT;

// ======================== OUT =======================
// valor de saida do fragment
layout(location = 0)out vec4 fColor;	// cor de saida do fragmento

// declaraçao de funçoes
// Funçao retorna o valor de influencia da luz ambient
vec4 AmbientLightValue();
// Funçao retorna o valor de influencia da luz direcional
vec4 DirectionalLightValue();
// Funçao retorna o valor de influencia da luz pontual
vec4 PointLightValue();
// Funçao retorna o valor de influencia da luz conica
vec4 SpotLightValue();

void main()
{
	// cor do fragmento de acordo com a textura
	vec4 tex_Color = texture(obj_texture,v2f_Tex_Coords);

	// define a cor ddo fragmento de acordo com a luz 
	fColor = (AmbientLightValue() + DirectionalLightValue() + PointLightValue() + SpotLightValue()) 
		* tex_Color;
}

// definiçao das funçoes
// calculo do valor da luz ambiente
vec4 AmbientLightValue(){
	// caso a luz ambiente nao estiver activa
	if(!AMBIENTLIGHT._ENABLE)
		return vec4(0.0f);	// retorna valor 0 de influencia
	// caso contrario retorna a influencia da luz no obj
	return vec4(MAT.KA_AMBIENT * AMBIENTLIGHT._COLOR , 1.0f);
}

// calculo do valor da luz direcional
vec4 DirectionalLightValue(){
	// caso a luz direcional nao esteja activa
	if(!DIRECTIONALLIGHT._ENABLE)
		return vec4(0.0f);	// retorna valor 0 de influencia
	// Componente ambiente
	// calculo da reflexao da componente ambiente da lyz
	vec4 ambient_val = vec4(MAT.KA_AMBIENT * DIRECTIONALLIGHT._AMBIENT_COMP,1.0f);

	// Componente difusa
	// guarda o valor de direcçao inverso á direçao original
	vec3 L = normalize(-DIRECTIONALLIGHT._DIRECTION);
	// guarda normais do objeto normalizadas
	vec3 N = normalize(v2f_Normals.xyz);
	// guarda o produto escalar entre a direcçao da luz e a normal do fragmento
	float NdotL = max(dot(N,L),0.0f);
	// determina o valor da componente difusa
	vec4 diffuse_val = vec4(MAT.KD_DIFUSE * DIRECTIONALLIGHT._DIFFUSE_COMP,1.0f) * NdotL;

	// componente especular
	// guarda o vetor de direcçao entre o fragmento e a posiçao da vista
	vec3 V = normalize(_VIEW_POS - v2f_Positions.xyz);
	// guarda o vetor refletido pela direçao da luz na normalizada
	vec3 R  = reflect(-L,N);
	// determina o produto escalar entre o vetor refletido e o vetor de vista
	float RdotV = max(dot(R,V),0.0f);
	// determina o valor da componente especular
	vec4 specular_val = pow(RdotV,MAT.NS_SPECULAR) * vec4(DIRECTIONALLIGHT._SPECULAR_COMP * MAT.KS_SPECULAR,1.0f);

	// retorna o valor de contribuiçao para a luz direcional
	return (ambient_val + diffuse_val + specular_val);
}

// calculo do valor da luz pontual
vec4 PointLightValue(){
	// caso a luz pontual nao esteja ativa
	if(!POINTLIGHT._ENABLE)
		return vec4(0.0f);	// retorna valor 0 para influencia

	// Componente ambiente
	// calculo da reflexao da componente ambiente da lyz
	vec4 ambient_val = vec4(MAT.KA_AMBIENT * POINTLIGHT._AMBIENT_COMP,1.0f);

	// componente difusa
	// guarda direçao da posiçao do fragmento para a posiçao da luz
	vec3 L = normalize(POINTLIGHT._POSITION - v2f_Positions.xyz);
	// guarda normal normalizada
	vec3 N = normalize(v2f_Normals.xyz);
	// determina o produto escalar entre a normal do fragmente e o vetor de direçao da luz ao fragmento
	float NdotL = max(dot(N,L),0.0f);
	// determina o valor da componente difusa
	vec4 diffuse_val = vec4(MAT.KD_DIFUSE * POINTLIGHT._DIFFUSE_COMP,1.0f) * NdotL;

	// componente especular
	// guarda o vetor de direçao entre o fragmento e a posiçao da vista
	vec3 V = normalize(_VIEW_POS - v2f_Positions.xyz);
	// guarda o vetor refletido pela direçao da luz determinada e a normal do fragmento
	vec3 R = reflect(-L , N);
	// determina o produto escalar entre o vetor refletido e o vetor de vista
	float RdotV = max(dot(R,V), 0.0f);
	// determina o valor da componente especular
	vec4 specular_val = pow(RdotV,MAT.NS_SPECULAR) * vec4(POINTLIGHT._SPECULAR_COMP * MAT.KS_SPECULAR,1.0f);

	// determina a atenuaçao para a luz
	// determina a distancia a que a luz encontra-se do fragmento
	float dist_to_frag = length(POINTLIGHT._POSITION - v2f_Positions.xyz);
	// calcula a atenuaçao de acordo com as constantes passadas
	float attenuation_val = 1.0f/(POINTLIGHT._CONSTANT_VAL + POINTLIGHT._LINEAR_VAL * dist_to_frag +
		POINTLIGHT._QUADRATIC_VAL * pow(dist_to_frag,2.0f));

	// retorna o valor de contribuiçao para a luz pontual
	return ((ambient_val + diffuse_val + specular_val) * attenuation_val);

}

// calculo do valor da luz conica
vec4 SpotLightValue(){
	// caso a luz conica nao esteja ativa
	if(!SPOTLIGHT._ENABLE)
		return vec4(0.0f);	// retorna valor 0 para a influencia

	// Componente ambiente
	// calculo da reflexao da componente ambiente da lyz
	vec4 ambient_val = vec4(MAT.KA_AMBIENT * SPOTLIGHT._AMBIENT_COMP,1.0f);

	// componente difusa
	// guarda direçao da posiçao do fragmento para a posiçao da luz
	vec3 L = normalize(SPOTLIGHT._POSITION - v2f_Positions.xyz);
	// guarda normal normalizada
	vec3 N = normalize(v2f_Normals.xyz);
	// determina o produto escalar entre a normal do fragmente e o vetor de direçao da luz ao fragmento
	float NdotL = max(dot(N,L),0.0f);
	// determina o valor da componente difusa
	vec4 diffuse_val = vec4(MAT.KD_DIFUSE * SPOTLIGHT._DIFFUSE_COMP,1.0f) * NdotL;

	// componente especular
	// guarda o vetor de direçao entre o fragmento e a posiçao da vista
	vec3 V = normalize(_VIEW_POS - v2f_Positions.xyz);
	// guarda o vetor refletido pela direçao da luz determinada e a normal do fragmento
	vec3 R = reflect(-L , N);
	// determina o produto escalar entre o vetor refletido e o vetor de vista
	float RdotV = max(dot(R,V), 0.0f);
	// determina o valor da componente especular
	vec4 specular_val = pow(RdotV,MAT.NS_SPECULAR) * vec4(SPOTLIGHT._SPECULAR_COMP * MAT.KS_SPECULAR,1.0f);

	// determina a atenuaçao para a luz
	// determina a distancia a que a luz encontra-se do fragmento
	float dist_to_frag = length(SPOTLIGHT._POSITION - v2f_Positions.xyz);
	// determina a influencia do cone , determinada pela direçao do cone e a direçao da luz ao fragmento
	float DdotV = dot(L, normalize(SPOTLIGHT._DIRECTION));

	// calcula a atenuaçao de acordo com as constantes passadas
	float attenuation_val = (1.0f * pow(DdotV, SPOTLIGHT._EXPONENT_VAL))/
		(SPOTLIGHT._CONSTANT_VAL + SPOTLIGHT._LINEAR_VAL * dist_to_frag + 
			SPOTLIGHT._QUADRATIC_VAL * pow(dist_to_frag,2.0f));

	// retorna o valor de contribuiçao para a luz pontual
	return ((ambient_val + diffuse_val + specular_val) * attenuation_val);
}