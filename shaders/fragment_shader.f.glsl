#version 400

in vec3 Normal;
in vec3 FragPos;

out vec4 FragColor;

void	main(void)
{
	vec3 objectColor = vec3(1.0f, 0.5f, 0.2f);
	vec3 ambient = 0.2 * objectColor;
	vec3 lightPos = vec3(100.0f, 100.0f, 100.0f);
	vec3 norm = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 lightColor = vec3(1.0f, 1.0f, 1.0f);
	vec3 diffuse = diff * lightColor;
	vec3 res = (ambient + diffuse) * objectColor;
	/* FragColor = vec4(res, 1.0f); */
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
