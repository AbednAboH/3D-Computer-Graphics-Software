#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoords;

// The model/view/projection matrices
uniform mat4 model;
uniform mat4 camera;
uniform mat4 view;
uniform mat4 projection;
uniform vec3 lightpos;
uniform vec3 viewpos;
// These outputs will be available in the fragment shader as inputs
out vec3 orig_fragPos;
out vec3 fragPos;
out vec3 fragNormal;
out vec2 fragTexCoords;
out vec3 Light;
out vec3 viewP;

void main()
{
	// Apply the model transformation to the 'position' and 'normal' properties of the vertex,
	// so the interpolated values of these properties will be available for usi n the fragment shader
	
	orig_fragPos = pos;
	fragPos = vec3(view  *camera* model *vec4(pos, 1.0f));
	fragNormal = mat3(view  *camera* model  ) * normal;
	Light= mat3(transpose(inverse(view  *camera* model ))) * lightpos;
	viewP=viewpos;

	//Pass the vertex texture coordinates property as it is. Its interpolated value
	//will be avilable for us in the fragment shader

	fragTexCoords = texCoords;
	

	// This is an internal OpenGL variable, we must set a value to this variable
	gl_Position = projection * view  *camera* model * vec4(pos, 1.0f);
}

