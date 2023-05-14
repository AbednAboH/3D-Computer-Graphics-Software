#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include "Renderer.h"
#include "InitShader.h"
#include "glm/gtc/matrix_transform.hpp"

glm::mat4x4 Renderer::bothmat = glm::mat4x4(1);
int Renderer::viewport_height = 1080;
int Renderer::viewport_width = 1920;

bool Renderer::ViewportChanged = false;
bool Renderer::enviroment = false;
bool Renderer::filledTriangls = true;
bool Renderer::light_on = false;
bool Renderer::IsSpherical = false;
bool Renderer::Refract = false;
float Renderer::deltaTheta = 0;
float Renderer::deltaPhi = 0;
float Renderer::ratio = 1;
int Renderer::type_sphere=3;

void Renderer::LoadShaders()
{
	colorShader.loadShaders("vshader.glsl", "fshader.glsl");
	EnviromentShader.loadShaders("vshader_enviroment.glsl", "fshader_enviroment.glsl");
	EnviromentCubeShader.loadShaders("vshader_reflectenv.glsl", "fshader_reflectenv.glsl");
}
vector<std::string> faces
{
	"..\\Data\\Enviroment1\\right.jpg","..\\Data\\Enviroment1\\left.jpg",
	"..\\Data\\Enviroment1\\top.jpg","..\\Data\\Enviroment1\\bottom.jpg",
	"..\\Data\\Enviroment1\\front.jpg","..\\Data\\Enviroment1\\back.jpg",
};

void Renderer::LoadTextures()
{
	if (!texture1.loadTexture("..\\Data\\S.png", true))
	{
		texture1.loadTexture("..\\Data\\S.png", true);
	}
}
void Renderer::LoadTextures(string str) {
	if (!texture1.loadTexture(str, true))
	{
		texture1.loadTexture(str, true);
	}
}
void Renderer::loadCubeMap() {
	
	texture1.LoadCubemap(faces);
}


Renderer::Renderer(int viewport_width, int viewport_height) 
{
	this->viewport_width = viewport_width;
	this->viewport_height = viewport_height;
}

Renderer::~Renderer()
{
	
}
void Renderer::lightandmodelshader(const Scene& scene) {
	glDepthFunc(GL_LESS);
	//bothmat = scene.GetActiveCamera().GetProjectionTransformation()* scene.GetActiveCamera().GetViewTransformation();
	colorShader.use();
	// Set the uniform variables
	colorShader.setUniform("model", scene.GetWorldMat() * scene.GetActiveModel().GetLocalMat());
	colorShader.setUniform("camera", glm::inverse(scene.GetActiveCamera().Cworld * scene.GetActiveCamera().CLocal));
	colorShader.setUniform("view", scene.GetActiveCamera().GetViewTransformation());
	colorShader.setUniform("projection", scene.GetActiveCamera().GetProjectionTransformation());
	colorShader.setUniform("material.textureMap", 0);
	colorShader.setUniform("material.ambient", scene.GetActiveModel().Material().GetAmbient());
	colorShader.setUniform("material.diffuse", scene.GetActiveModel().Material().GetDiffuse());
	colorShader.setUniform("material.specular", scene.GetActiveModel().Material().GetSpecular());
	colorShader.setUniform("material.select", light_on);
	colorShader.setUniform("material.TextureOnOff", scene.textures);
	colorShader.setUniform("material.IsSpherical", IsSpherical);
	colorShader.setUniform("material.deltaTheta",deltaTheta);
	colorShader.setUniform("material.deltaPhi", deltaPhi);
	colorShader.setUniform("material.color", scene.Objcolor);
	colorShader.setUniform("material.type", type_sphere);

	//colorShader.setUniform("material.alpha",scene.GetLight(0).Material().GetIntensity());
	if (scene.GetLightCount() > 0) {
		colorShader.setUniform("PointLight.position", scene.GetLight(0).move);
		colorShader.setUniform("material.alpha", scene.GetLight(0).Material().GetIntensity());
		colorShader.setUniform("lightmat.ambient", scene.GetLight(0).Material().GetAmbient());
		colorShader.setUniform("lightmat.diffuse", scene.GetLight(0).Material().GetDiffuse());
		colorShader.setUniform("lightmat.specular", scene.GetLight(0).Material().GetSpecular());
		colorShader.setUniform("lightpos", scene.GetLight(0).move);
	}
	else {
		colorShader.setUniform("lightpos", 0);
		colorShader.setUniform("material.alpha", 1);

	}
	colorShader.setUniform("viewpos", scene.GetActiveCamera().eye);


	// Set 'texture1' as the active texture at slot #0
	texture1.bind(0);

	// Drag our model's faces (triangles) in fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(scene.GetActiveModel().GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, scene.GetActiveModel().GetModelVertices().size());
	glBindVertexArray(0);

	// Unset 'texture1' as the active texture at slot #0
	texture1.unbind(0);
	if (scene.GetLightCount() > 0) {
		colorShader.use();
		// Set the uniform variables
		colorShader.setUniform("model", scene.GetWorldMat() * scene.GetLight(0).GetLocalMat());
		//colorShader.setUniform("camera", scene.GetActiveModel().GetLocalMat());
		colorShader.setUniform("view", scene.GetActiveCamera().GetViewTransformation());
		colorShader.setUniform("projection", scene.GetActiveCamera().GetProjectionTransformation());
		colorShader.setUniform("material.textureMap", 0);
		colorShader.setUniform("material.ambient", scene.GetActiveModel().Material().GetAmbient());
		colorShader.setUniform("material.diffuse", scene.GetActiveModel().Material().GetDiffuse());
		colorShader.setUniform("material.specular", scene.GetActiveModel().Material().GetSpecular());
		colorShader.setUniform("material.select", false);
		colorShader.setUniform("material.alpha", 0);
		if (scene.GetLightCount() > 0)
			colorShader.setUniform("lightpos", scene.GetLight(0).move);

		else colorShader.setUniform("lightpos", 0);
		colorShader.setUniform("viewpos", scene.GetActiveCamera().eye);
		// Set 'texture1' as the active texture at slot #0
		texture1.bind(0);
		// Drag our model's faces (triangles) in fill mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(scene.GetLight(0).GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, scene.GetLight(0).GetModelVertices().size());
		glBindVertexArray(0);
		// Unset 'texture1' as the active texture at slot #0
		texture1.unbind(0);
	}
}
void Renderer::Enviromentmode(const Scene& scene)  {


	glDepthFunc(GL_LESS);
	EnviromentCubeShader.use();
	EnviromentCubeShader.setUniform("viewpos", scene.GetActiveCamera().eye);
	EnviromentCubeShader.setUniform("model", scene.GetWorldMat() * scene.GetActiveModel().GetLocalMat());
	EnviromentCubeShader.setUniform("view", scene.GetActiveCamera().GetViewTransformation());
	EnviromentCubeShader.setUniform("projection", glm::inverse(scene.GetActiveCamera().Cworld * scene.GetActiveCamera().CLocal) * scene.GetActiveCamera().GetProjectionTransformation());
	EnviromentCubeShader.setUniform("ratio",ratio);
	EnviromentCubeShader.setUniform("Refract",Refract);
	texture1.bindCube(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(scene.GetActiveModel().GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, scene.GetActiveModel().GetModelVertices().size());
	glBindVertexArray(0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(scene.GetActiveModel().GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, scene.GetActiveModel().GetModelVertices().size());
	glBindVertexArray(0);
	texture1.unbindCube(0);
	// Drag our model's faces (triangles) in line mode (wireframe)
	


	///enviroment rendering
	glDepthFunc(GL_LEQUAL);
	EnviromentShader.use();
	texture1.bindCube(0);
	EnviromentShader.setUniform("view", scene.GetActiveCamera().GetViewTransformation());
	EnviromentShader.setUniform("projection", glm::inverse(scene.GetActiveCamera().Cworld * scene.GetActiveCamera().CLocal) * scene.GetActiveCamera().GetProjectionTransformation());
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glBindVertexArray(scene.GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
	texture1.unbindCube(0);
}
void Renderer::WireFrame(const Scene& scene) {
	glDepthFunc(GL_LESS);
	//bothmat = scene.GetActiveCamera().GetProjectionTransformation()* scene.GetActiveCamera().GetViewTransformation();
	colorShader.use();
	// Set the uniform variables
	colorShader.setUniform("model", scene.GetWorldMat() * scene.GetActiveModel().GetLocalMat());
	colorShader.setUniform("camera", glm::inverse(scene.GetActiveCamera().Cworld * scene.GetActiveCamera().CLocal));
	colorShader.setUniform("view", scene.GetActiveCamera().GetViewTransformation());
	colorShader.setUniform("projection", scene.GetActiveCamera().GetProjectionTransformation());
	colorShader.setUniform("material.textureMap", 0);
	colorShader.setUniform("material.ambient", scene.GetActiveModel().Material().GetAmbient());
	colorShader.setUniform("material.diffuse", scene.GetActiveModel().Material().GetDiffuse());
	colorShader.setUniform("material.specular", scene.GetActiveModel().Material().GetSpecular());
	colorShader.setUniform("material.select", true);

	//colorShader.setUniform("material.alpha",scene.GetLight(0).Material().GetIntensity());
	if (scene.GetLightCount() > 0) {
		colorShader.setUniform("PointLight.position", scene.GetLight(0).move);
		colorShader.setUniform("material.alpha", scene.GetLight(0).Material().GetIntensity());
		colorShader.setUniform("lightmat.ambient", scene.GetLight(0).Material().GetAmbient());
		colorShader.setUniform("lightmat.diffuse", scene.GetLight(0).Material().GetDiffuse());
		colorShader.setUniform("lightmat.specular", scene.GetLight(0).Material().GetSpecular());
		colorShader.setUniform("lightpos", scene.GetLight(0).move);
	}
	else {
		colorShader.setUniform("lightpos", 0);
		colorShader.setUniform("material.alpha", 1);

	}
	colorShader.setUniform("viewpos", scene.GetActiveCamera().eye);


	// Set 'texture1' as the active texture at slot #0
	texture1.bind(0);

	// Drag our model's faces (triangles) in fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBindVertexArray(scene.GetActiveModel().GetVAO());
	glDrawArrays(GL_TRIANGLES, 0, scene.GetActiveModel().GetModelVertices().size());
	glBindVertexArray(0);

	// Unset 'texture1' as the active texture at slot #0
	texture1.unbind(0);
	if (scene.GetLightCount() > 0) {
		colorShader.use();
		// Set the uniform variables
		colorShader.setUniform("model", scene.GetWorldMat() * scene.GetLight(0).GetLocalMat());
		//colorShader.setUniform("camera", scene.GetActiveModel().GetLocalMat());
		colorShader.setUniform("view", scene.GetActiveCamera().GetViewTransformation());
		colorShader.setUniform("projection", scene.GetActiveCamera().GetProjectionTransformation());
		colorShader.setUniform("material.textureMap", 0);
		colorShader.setUniform("material.ambient", scene.GetActiveModel().Material().GetAmbient());
		colorShader.setUniform("material.diffuse", scene.GetActiveModel().Material().GetDiffuse());
		colorShader.setUniform("material.specular", scene.GetActiveModel().Material().GetSpecular());
		colorShader.setUniform("material.select", false);
		colorShader.setUniform("material.alpha", 0);
		if (scene.GetLightCount() > 0)
			colorShader.setUniform("lightpos", scene.GetLight(0).move);

		else colorShader.setUniform("lightpos", 0);
		colorShader.setUniform("viewpos", scene.GetActiveCamera().eye);
		// Set 'texture1' as the active texture at slot #0
		texture1.bind(0);
		// Drag our model's faces (triangles) in fill mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glBindVertexArray(scene.GetLight(0).GetVAO());
		glDrawArrays(GL_TRIANGLES, 0, scene.GetLight(0).GetModelVertices().size());
		glBindVertexArray(0);
		// Unset 'texture1' as the active texture at slot #0
		texture1.unbind(0);
	}
}
void Renderer::Render(const Scene& scene)
{
	scene.GetActiveCamera().SetCameraLookAt(scene.GetActiveCamera().eye, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	switch (scene.mode) 
	{
		case 0:
			Enviromentmode(scene);
			break;
		case 1:
			lightandmodelshader(scene);
			break;
		case 2:
			WireFrame(scene);
		default:
			WireFrame(scene);

	}
	
	
}

int Renderer::GetViewportWidth() {return viewport_width;}

int Renderer::GetViewportHeight() {return viewport_height;}

void Renderer::SetWidthHeight(int height, int width)
{viewport_height = height;	viewport_width=width;}




/*x01 = Interpolate(p0.y, p0.x, p1.y, p1.x);
		x12 = Interpolate(p1.y, p1.x, p2.y, p2.x);
		x02 = Interpolate(p0.y, p0.x, p2.y, p2.x);
		x01.pop_back();
		x01.insert(x01.end(), x12.begin(), x12.end());*/
		//z01 = Interpolate(p0.y, 1 / p0.z, p1.y, 1 / p1.z);
		//z12 = Interpolate(p1.y, 1 / p1.z, p2.y, 1 / p2.z);
		//z02 = Interpolate(p0.y, 1 / p0.z, p2.y, 1 / p2.z);
		//z01.pop_back();
		//z01.insert(z01.end(), z12.begin(), z12.end());
		//m = floor(x01.size() / 2);
		//bool leftright;
		//if (x02[m] < x01[m]) {
		//	/*x_left = x02;
		//	x_right = x01;*/
		//	zleft = z02;
		//	zright = z01;
		//	leftright = true;//p1 is on the right
		//}
		//else {
		//	/*x_left = x01;
		//	x_right = x02;*/
		//	zleft = z01;
		//	zright = z02;
		//	leftright = false;//p1 is on the left handside
		//}