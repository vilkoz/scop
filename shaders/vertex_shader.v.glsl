#version 400
layout (location = 0) in vec3	aPos;
layout (location = 1) in vec3	aNormal;
layout (location = 2) in vec2	aUV;

uniform mat4					model;
uniform mat4					view;
uniform mat4					projection;

out vec3						Normal;
out vec3						FragPos;
out vec2						UV;
out vec3						WorldPos;
out vec3						tex_coords;

void	main(void)
{
	gl_Position = (projection * view * model) * vec4(aPos.x, aPos.y, aPos.z, 1.0);
	Normal = normalize(vec3(model * vec4(aNormal, 0.0)));
	/* Normal = aNormal; */
	FragPos = vec3(view * model * vec4(aPos, 1.0));
	WorldPos = vec3(model * vec4(aPos, 1.0));
	UV = aUV;
	tex_coords = aPos;
}
