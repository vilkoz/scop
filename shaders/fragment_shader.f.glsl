#version 400

in vec2					UV;
uniform sampler2D		textureSampler;

uniform int				shading;
uniform vec3			ka;
uniform vec3			kd;
uniform vec3			ks;
uniform float			ns;
uniform vec3			camPos;
in vec3					Normal;
in vec3					FragPos;
in vec3					WorldPos;

out vec4				FragColor;

void	main(void)
{
	vec3 objectColor = kd;
	vec3 ambient = ka;
	vec3 lightPos = vec3(100.0f, 100.0f, 100.0f);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	/* vec3 lightColor = kd; */
	vec3 diffuse = diff * lightColor;
	// specular
	vec3 eye = normalize(camPos - WorldPos);
	vec3 light_reflect = normalize(reflect(eye, Normal));
	float specular_factor = dot(eye, light_reflect);
	vec3 specular;
	if (specular_factor < 0)
	{
		specular_factor = pow(abs(specular_factor), ns);
		specular = ks * specular_factor;
	}
	else
		specular = vec3(0.0f, 0.0f, 0.0f);

	vec3 res = (ambient + diffuse + specular) * objectColor;
	/* vec3 res = (ambient + diffuse) * objectColor; */
	if (shading == 0)
	{
		FragColor = vec4(res, 1.0f);
	}
	else if (shading == 1)
	{
		FragColor = vec4(abs(Normal.x), abs(Normal.y), abs(Normal.z), 1.0);
	}
	else
	{
		FragColor = texture(textureSampler, UV) * vec4(res, 1.0);
	}
}
