#version 330 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;

out vec3 fragnormal;
out vec3 fragpos;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model; 

void main()
{
		fragnormal=mat3(transpose(inverse( model)))*normal;
		fragpos=vec3(model*vec4(pos,1.0));
		gl_Position = projection * view *model* vec4(pos,1.0);
}
