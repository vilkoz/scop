#version 400

uniform int		shading;
in vec3			Normal;
in vec3			FragPos;

out vec4		FragColor;

void	main(void)
{
	vec3 objectColor = vec3(0.7f, 0.7f, 0.7f);
	vec3 ambient = 0.2 * objectColor;
	vec3 lightPos = vec3(100.0f, 100.0f, 100.0f);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 diffuse = diff * lightColor;
	vec3 res = (ambient + diffuse) * objectColor;
	if (shading == 0)
	{
		FragColor = vec4(res, 1.0f);
	}
	else if (shading == 1)
	{
		vec3 normal = vec3(abs(Normal.x), abs(Normal.y), abs(Normal.z));
		FragColor = vec4(normal, 1.0);
	}
	else
	{
		FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f) * vec4(res, 1.0);
	}
}
