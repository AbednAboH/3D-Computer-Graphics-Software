#include "light.h"
light::light(glm::vec3 position,glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : position(position) ,ambient(ambient),
diffuse(diffuse), specular(specular) {
	intensity = 0;
	center = glm::vec3(0);
}

void light::SetALL(glm::vec3 amb, glm::vec3 deff, glm::vec3 spec){specular = spec;diffuse = deff;ambient = amb;}

void light::SetAmbient(glm::vec3 vec){ambient=vec;}

void light::SetDiffuse(glm::vec3 vec){	diffuse = vec;}

void light::SetSpecular(glm::vec3 vec){specular = vec;}

void light::SetPosition(glm::vec3 vec){position = vec;}

void light::SetCenter(glm::vec3 vec)
{
	center = vec;
}

void light::SetIntensity(float intensity)
{
	this->intensity = intensity;
}

glm::vec3 light::GetAmbient(){return ambient;}

glm::vec3 light::GetDiffuse(){	return diffuse;}

glm::vec3 light::GetSpecular(){return specular;}

glm::vec3 light::GetPosition(){return position;}

glm::vec3 light::GetCenter()
{
	return center;
}

float light::GetIntensity()
{
	return intensity;
}
