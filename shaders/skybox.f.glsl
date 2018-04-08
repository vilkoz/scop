#version 400
uniform samplerCube		sampler_cube;

in vec3					tex_coords;


out vec4				FragColor;
void main()
{
		FragColor = texture(sampler_cube, tex_coords);
}
