#pragma once
#define _USE_MATH_DEFINES
#include <vector>
#include <memory>
#include "Camera.h"
#include "MeshModel.h"

using namespace std;

class Scene {
public:
	Scene();

	void AddModel(const shared_ptr<MeshModel>& mesh_model);
	int GetModelCount() const;
	MeshModel& GetModel(int index) const;
	MeshModel& GetActiveModel() const;

	void AddCamera(const shared_ptr<Camera>& camera);
	int GetCameraCount() const;
	
	Camera& GetCamera(int index) const;
	Camera& GetActiveCamera() const;

	void SetActiveCameraIndex(int index);
	int GetActiveCameraIndex() const;
	
	
	void SetActiveModelIndex(int index);
	int GetActiveModelIndex() const;
	
	void Addlight(const shared_ptr<MeshModel>& light);
	int GetLightCount() const;
	void Scene::RemoveLight(int index);

	MeshModel& GetLight(int index) const;
	//light& GetActiveLight() const;
	
	
	void SetWorldMat();
	void SetT(glm::mat4 k);
	void SetS(glm::mat4 k);
	void SetR(glm::mat4 k);
	glm::mat4x4 GetWorldMat() const;



	glm::mat4 object_mat(int modelnumber, bool lightOrMesh=false) const;
	glm::mat4 World_mat(glm::vec3 move, glm::vec3 Rotate, glm::vec3 scale);
	glm::mat4 axisMat(int modelnumber) const;
	glm::vec3 Objcolor;
	static glm::vec3 wRotate;//move object up or down
	static glm::vec3 wmove;//move object up or down
	static glm::vec2 uniform;
	static bool PerFace;
	static bool PerVertix;
	static bool snap;
	static bool pers_ortho;
	static bool show_axis;
	static bool show_obj_axis;
	static bool show_BRec;
	static bool point;
	static bool showpoint;
	static bool showrays;
	static bool flat;
	static float sigma;
	static int mode;
	static bool textures;
	static glm::vec4 PerFaceColor;
	static glm::vec4 PerVertixColor;
	static glm::vec4 BboxColor;
	GLuint GetVAO() const;
	
private:
	vector<shared_ptr<MeshModel>> mesh_models;
	vector<shared_ptr<MeshModel>> lights;
	vector<shared_ptr<Camera>> cameras;
	int active_camera_index;
	int active_model_index;
	glm::mat4 world_mat;
	glm::mat4 T;
	glm::mat4 R;
	glm::mat4 S;
	//cube Vertix array and vertix object
	GLuint Skyvao, Skyvbo;

	

};