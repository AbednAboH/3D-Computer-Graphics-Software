#include "Camera.h"
#include "glm/gtc/matrix_transform.hpp"
glm::vec3 Camera::eye = glm::vec3(0, 0,2.f);
float Camera::l =-1.325;
float Camera::b = -0.9975;
float Camera::f = 100.f;
float Camera::r = 1.325;
float Camera::t = 0.9975;
float Camera::n = 0.1f;
float Camera::TOrtho = 20;
float Camera::Tperspective = glm::radians(120.f);
glm::vec3 Camera::scale = glm::vec3(1, 1, 1);
glm::vec3 Camera::move = glm::vec3(0, 0, 0);
glm::vec3 Camera::Rotate = glm::vec3(0, 0, 0);

Camera::Camera()
{
	view_transformation = glm::mat4(1.f);

	projection_transformation =glm::mat4(1.f);
	CLocal = glm::mat4(1);
	Cworld= glm::mat4(1);
}

Camera::~Camera()
{
	
}
	
void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up)
{
	//if (eye != glm::vec3(0.f, 0.f, 0.f))
		view_transformation = glm::lookAt(eye, at, up);
	//else
		//view_transformation = glm::mat4(0);
}

void Camera::SetViewTrans(float OrthoPers,float aspectRatio)
{
	if (OrthoPers)
		projection_transformation=glm::ortho(l, r, b, t, n, f);
	//else projection_transformation = glm::frustum(l, r, b, t, n, f);
	else projection_transformation = glm::perspective(Tperspective,aspectRatio,n,f);

}

const glm::mat4x4& Camera::GetProjectionTransformation() const
{
	return projection_transformation;
}

const glm::mat4x4& Camera::GetViewTransformation() const
{
	return view_transformation;
}
const glm::mat4& Camera::SetLocal(glm::vec3 move, glm::vec3 Rotate, glm::vec3 scale) {
	return CLocal= glm::translate(glm::mat4(1), move) * glm::rotate(glm::mat4(1), (float)(Rotate.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), (float)(Rotate.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1), (float)Rotate.z, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), scale);
}
const glm::mat4& Camera::SetWorld(glm::vec3 move, glm::vec3 Rotate, glm::vec3 scale) {
	return Cworld=glm::translate(glm::mat4(1), move) * glm::rotate(glm::mat4(1), (float)(Rotate.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), (float)(Rotate.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1), (float)Rotate.z, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), scale);

}