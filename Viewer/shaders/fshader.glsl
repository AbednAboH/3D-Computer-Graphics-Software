#version 330 core
#define PI 3.1415926538
struct Material
{
	sampler2D textureMap;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	bool select;
	float alpha ;
	float deltaTheta;
	float deltaPhi;
	bool TextureOnOff;
	bool IsSpherical;
	int type;
	vec3 color;
	
};
struct Lights
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


// We set this field's properties from the C++ code
uniform Material material;
uniform Lights lightmat;

//taken from the book given in the lecture 

vec3 phongshading(vec3 amb,vec3 dif,vec3 mspec,vec3 lamb,vec3 ldif,vec3 lspec,vec3 fragNormal,vec3 viewP,vec3 Light,vec3 fragPos)
{
			vec3 normal = normalize(fragNormal);
			vec3 viewDir = normalize(viewP - fragPos);//v
			vec3 lightDir = normalize(Light - fragPos);	//I
			float spec=0;

			// diffuse shading
			float diff = max(dot(normal, lightDir), 0.0);
			
			// specular shading
			vec3 reflectDir = reflect(-lightDir, normal);
			
		
			spec = pow(max(dot(viewDir, reflectDir), 0.0),material.alpha);
			

	
			vec3 ambient = amb*lamb;
			vec3 diffuse =dif *diff *ldif;
			vec3 specular =mspec *spec*lspec;
			
			vec3 result=ambient+diffuse+specular;
			return result;
}

vec2 SphericalMapping(vec3 orig_fragPos,float deltaPhi,float deltaTheta,int axis)
{
		if (axis==1)
		{
			float r =sqrt(pow(orig_fragPos.x,2)+pow(orig_fragPos.y,2)+pow(orig_fragPos.z,2));
			float theta=atan(orig_fragPos.y/orig_fragPos.x);
			float phi=acos(orig_fragPos.z/r);
			return vec2(phi+deltaPhi,theta+deltaTheta);
			
		}
		else if (axis==2)
		{
			orig_fragPos=normalize(orig_fragPos);
			float r =sqrt(pow(orig_fragPos.x,2)+pow(orig_fragPos.y,2)+pow(orig_fragPos.z,2));
			float theta=atan(orig_fragPos.z/orig_fragPos.x)/(2*PI)+0.5;
			float phi=acos(orig_fragPos.y/r)/PI+0.5;
			return vec2(phi+deltaPhi,theta+deltaTheta);
		}
		else 
		{
			// use mirroring to our advantage 	
			orig_fragPos=normalize(orig_fragPos);
			float r =sqrt(pow(orig_fragPos.x,2)+pow(orig_fragPos.y,2)+pow(orig_fragPos.z,2));
			float theta=atan(orig_fragPos.z/orig_fragPos.x);
			float phi=acos(orig_fragPos.y/r);
			return vec2(phi+deltaPhi,theta+deltaTheta);
		}
		
}

// Inputs from vertex shader (after interpolation was applied)
in vec3 fragPos;
in vec3 fragNormal;
in vec2 fragTexCoords;
in vec3 orig_fragPos;
in vec3 Light;
in vec3 viewP;
// The final color of the fragment (pixel)
out vec4 frag_color;

void main()
{
		vec3 textureColor=vec3(0);
		vec3 result=vec3(0);
		//calculate spherical mapping :
		if (material.IsSpherical)
		{
			vec2 Spherical =SphericalMapping(orig_fragPos,material.deltaPhi,material.deltaTheta,material.type);
			textureColor = vec3(texture(material.textureMap, Spherical).rgb);
		}
		else {
		// Sample the texture-map at the UV coordinates given by 'fragTexCoords' 
		// i.e given by the model .
			textureColor = vec3(texture(material.textureMap, fragTexCoords).rgb);
		}
		//if light switch is on 
		if (material.select)
		{
			// calculate phong shading 
			
			result=phongshading(material.ambient,material.diffuse,material.specular,lightmat.ambient,lightmat.diffuse,lightmat.specular,fragNormal,viewP,Light,fragPos);
			
			//show textures 

			if (material.TextureOnOff)
			{
			result=result*textureColor;
			}
		}
		else 
		{
			// if we should display textures ,pay no attention to color 
			if (material.TextureOnOff){result=textureColor;}
			else {result=material.color;}
		}

		
		frag_color =vec4(result.rgb,1);
}
