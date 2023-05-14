#pragma once
#include <glm/glm.hpp>
#include<ostream>
#include<iostream>
#include "Face.h"
#include "light.h"
#include "glm/gtc/matrix_transform.hpp"
struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texture;
};
class MeshModel
{
public:
	MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textures, const std::string& model_name);
	virtual ~MeshModel();
	const Face& GetFace(int index) const;
	int GetFacesCount() const;
	const std::string& GetModelName() const;
	void SetVertixNormals();
	std::vector<glm::vec4> GetVertixNormals();
	void SetFaceBRecColor();
	std::vector<glm::vec4> SetFaceNormals(std::vector<glm::vec4>& vec);
	std::vector<glm::vec4>& GetFaceNormals();
	std::vector<glm::vec4>& GetFaceBRecColors();
	std::vector<glm::vec4>& GetMidFaceNormals();
	std::vector<glm::vec4>& GetFCorrectedVertix();
	void  ReCalibrateParameters(int halfheight, int halfwidth);
	std::vector<glm::vec4> ModelAxis(float c);
	friend std::ostream& operator<< (std::ostream& o, MeshModel const& mesh);
	glm::vec4 findRatio(int midheight, int midwidth,int swich);
	std::vector<float> findMaxMin(std::vector<glm::vec4> vec);
	std::vector<float> MeshModel::findMaxMin(std::vector<glm::vec2> vec);
	glm::vec4 GetTranslation();
	glm::ivec3 GetVector(int i);
	glm::vec4 GetVectorAsVec4(int i);
	glm::mat4 GetLocalMat();
	void SetBbox(std::vector<float> vec);
	std::vector<glm::vec4>& GetBbox();
	int Getvectorsize();
	glm::ivec2 GetHeightWidth();
	void SetHeightWidth(int height,int width);
	void update_local();
	void update_T(glm::mat4 k);
	void update_R(glm::mat4 k);
	void update_S(glm::mat4 k);
	GLuint GetVAO() const;
	light& Material();
	glm::vec3 Rotate;//rotate around x,y,z 
	glm::vec3 move;//move object up or down
	glm::vec3 scale ;//3 scales one for x ,one for y ,one for z
	bool Bounding;
	float ortho;

	const std::vector<Vertex>& GetModelVertices();
private:
	std::vector<Face> faces;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> textures;
	std::vector<glm::vec4> CorrectedFaceNormals;
	std::vector<glm::vec4> CorrectedVertixNormals;
	std::vector<glm::vec4> NormalsFromMidFace;
	std::vector<glm::vec4> CorrectedVertices;
	std::vector<glm::vec4> FaceBRecColors;
	std::vector<Vertex> modelver;
	std::string model_name;
	glm::vec4 Translation;
	glm::mat4 model_mat;
	glm::mat4 T;
	glm::mat4 S;
	glm::mat4 R;
	std::vector<glm::vec3> axis;
	std::vector<glm::vec4> Bbox; //bounding box 
	std::vector<std::vector<int>> FacesAdjecency;
	light material;
	
	GLuint vbo;
	GLuint vao;

	static int height, width;
};
