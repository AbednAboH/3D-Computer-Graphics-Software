#version 330 core

out vec4 frag_color;

in vec3 fragnormal;
in vec3 fragpos;

uniform float ratio;
uniform vec3 viewpos;
uniform samplerCube cube;
uniform bool Refract;
void main()
{	
		//ray direction 
		vec3 Raydir=normalize(fragpos-viewpos);
		vec3 Reflection=reflect(Raydir,normalize(fragnormal));
		if (Refract)
		{
			Reflection=refract(Raydir,normalize(fragnormal),ratio);
		}
		frag_color =vec4(texture(cube ,Reflection).rgb,1.0);	
	
}
