#pragma once
#include <glm/glm.hpp>

class Camera
{
public:
	Camera();
	virtual ~Camera();
	
	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	void SetViewTrans(float OrthoPers,float aspectRatio);
	const glm::mat4x4& GetProjectionTransformation() const;
	const glm::mat4x4& GetViewTransformation() const;
	const glm::mat4& SetLocal(glm::vec3 move, glm::vec3 Rotate, glm::vec3 scale);
	const glm::mat4& SetWorld(glm::vec3 move, glm::vec3 Rotate, glm::vec3 scale);
	static glm::vec3 eye;
	static float l, r, t, b, n, f,TOrtho,Tperspective;
	static glm::vec3 Rotate;//rotate around x,y,z 
	static glm::vec3 move;//move object up or down
	static glm::vec3 scale;//3 scales one for x ,one for y ,one for z
	glm::mat4 Cworld;
	glm::mat4 CLocal;
private:
	
	//transformation of the camera itself
	glm::mat4 view_transformation;
	glm::mat4 projection_transformation;
	


};
