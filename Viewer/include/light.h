#include <glad/glad.h>
#include <glm/glm.hpp>
class light
{
public:
	light(glm::vec3 position= glm::vec3(0),glm::vec3 ambient= glm::vec3(1), glm::vec3 diffuse = glm::vec3(1), glm::vec3 specular = glm::vec3(1));
	void SetALL(glm::vec3 amb, glm::vec3 deff, glm::vec3 spec);
	void SetAmbient(glm::vec3 vec);
	void SetDiffuse(glm::vec3 vec);
	void SetSpecular(glm::vec3 vec);
	void SetPosition(glm::vec3 vec);
	void SetCenter(glm::vec3 vec);
	void SetIntensity(float intensity);
	glm::vec3 GetAmbient();
	glm::vec3 GetDiffuse();
	glm::vec3 GetSpecular();
	glm::vec3 GetPosition();
	glm::vec3 GetCenter();
	float GetIntensity();
private :
	float intensity;
	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;
	glm::vec3 position;
	glm::vec3 center;
	

};

