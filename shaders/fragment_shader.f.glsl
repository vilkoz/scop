#version 400

in vec2					UV;
uniform sampler2D		textureSampler;
uniform samplerCube		sampler_cube;

uniform int				is_cubemap;
uniform int				shading;
uniform vec3			ka;
uniform vec3			kd;
uniform vec3			ks;
uniform float			ns;
uniform vec3			camPos;
in vec3					Normal;
in vec3					FragPos;
in vec3					WorldPos;

in vec3					tex_coords;

out vec4				FragColor;

vec3	calc_diffuse_color(vec3 objectColor, vec3 lightPos, vec3 lightColor)
{
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;
	return diffuse;
}

vec3	calc_specular_color(vec3 lightPos)
{
	vec3 eye = normalize(camPos - WorldPos);
	vec3 lightDir = normalize(lightPos - FragPos);
	vec3 light_reflect = normalize(reflect(lightDir, Normal));
	float specular_factor = dot(eye, light_reflect);
	vec3 specular;
	if (specular_factor < 0)
	{
		specular_factor = pow(abs(specular_factor), ns);
		specular = ks * specular_factor;
	}
	else
		specular = vec3(0.0f, 0.0f, 0.0f);
	return specular;
}

vec3	calc_color_for_ligth_source(vec3 lightPos, vec3 lightColor)
{
	vec3 objectColor = kd;
	vec3 ambient = ka;
	vec3 diffuse = calc_diffuse_color(objectColor, lightPos, lightColor);
	vec3 specular = calc_specular_color(lightPos);
	vec3 res = (ambient + diffuse + specular) * objectColor;
	return (res);
}

void	main(void)
{
	if (is_cubemap == 1)
	{
		FragColor = texture(sampler_cube, tex_coords);
		return ;
	}
	vec3 res = calc_color_for_ligth_source(vec3(100.f, 100.f, 100.f), vec3(1.f, 1.f, 1.f));
	res += calc_color_for_ligth_source(vec3(-100.f, -100.f, -100.f), vec3(1.f, 0.f, 1.f));
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
