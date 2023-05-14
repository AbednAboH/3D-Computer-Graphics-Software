#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <map>
#include <list>
#include "ShaderProgram.h"
#include "Texture2D.h"
class Renderer
{
public:
	void LoadShaders();
	void LoadTextures();
	void LoadTextures(string str);
	void loadCubeMap();
	Renderer(int viewportWidth, int viewportHeight);
	virtual ~Renderer();
	void lightandmodelshader(const Scene& scene);
	void Enviromentmode(const Scene& scene);
	void WireFrame(const Scene& scene);
	void Render(const Scene& scene);
	static int GetViewportWidth()  ;
	static int GetViewportHeight() ;
	static bool ViewportChanged;
	static void SetWidthHeight(int height, int width);
	static glm::mat4 bothmat;
	static bool enviroment;
	static bool filledTriangls;
	static bool light_on;
	static bool IsSpherical;
	static bool Refract;
	static float deltaTheta;
	static float deltaPhi;
	static float ratio;
	static int type_sphere;
private:
	
	
	std::list<glm::vec3>  lighting_buffer;
	static int viewport_width;
	static int viewport_height;
	ShaderProgram lightShader;
	ShaderProgram colorShader;
	ShaderProgram EnviromentShader;
	ShaderProgram EnviromentCubeShader;
	Texture2D texture1;
};
