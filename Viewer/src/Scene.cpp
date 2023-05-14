#include "Scene.h"
#include "MeshModel.h"
#include <string>

glm::vec3 Scene::wRotate = glm::vec3(0,0.0, 0.0);
glm::vec3 Scene::wmove = glm::vec3(0,0.0, 0.0);
glm::vec2 Scene::uniform = glm::vec2(1.0, 1.0);
glm::vec4 Scene::PerFaceColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.f);
glm::vec4 Scene::PerVertixColor = glm::vec4(1.0f, 1.0f, 0.0f, 1.f);
glm::vec4 Scene::BboxColor = glm::vec4(0.f, 0.0f, 1.f, 1.f);
bool Scene::PerFace = false;
bool Scene::PerVertix = false;
bool Scene::pers_ortho = false;
bool Scene::show_axis = true;
bool Scene::show_obj_axis = true;
bool Scene::snap = false;
bool Scene::show_BRec = false;
bool Scene::point = false;
bool Scene::showpoint = false;
bool Scene::showrays = false;
bool Scene::flat = false;
bool Scene::textures = false;
float Scene::sigma =0.5;
int Scene::mode = 0;
float skyboxVertices[] = {
    // positions          
    -1.0f,  1.0f, -1.0f,
    -1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f, -1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,

    -1.0f, -1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f, -1.0f,  1.0f,
    -1.0f, -1.0f,  1.0f,

    -1.0f,  1.0f, -1.0f,
     1.0f,  1.0f, -1.0f,
     1.0f,  1.0f,  1.0f,
     1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f,  1.0f,
    -1.0f,  1.0f, -1.0f,

    -1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f, -1.0f,
     1.0f, -1.0f, -1.0f,
    -1.0f, -1.0f,  1.0f,
     1.0f, -1.0f,  1.0f
};
Scene::Scene() :
	active_camera_index(0),
	active_model_index(0)
{
	Objcolor = glm::vec4(1.0f, 1.0f, 1.0f, 1.00f);
	world_mat=R=S=T = glm::mat4(1);
    glGenVertexArrays(1, &Skyvao);
    glGenBuffers(1, &Skyvbo);
    glBindVertexArray(Skyvao);
    glBindBuffer(GL_ARRAY_BUFFER, Skyvbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
}

void Scene::AddModel(const std::shared_ptr<MeshModel>& mesh_model)
{
	mesh_models.push_back(mesh_model);
}

int Scene::GetModelCount() const
{
	return mesh_models.size();
}

MeshModel& Scene::GetModel(int index) const
{
	return *mesh_models[index];
}

MeshModel& Scene::GetActiveModel() const
{
	return *mesh_models[active_model_index];
}

void Scene::AddCamera(const std::shared_ptr<Camera>& camera)
{
	cameras.push_back(camera);
}

int Scene::GetCameraCount() const
{
	return cameras.size();
}

Camera& Scene::GetCamera(int index) const
{
	return *cameras[index];
}

Camera& Scene::GetActiveCamera() const
{
	return *cameras[active_camera_index];
}

void Scene::SetActiveCameraIndex(int index) 
{
	active_camera_index = index;
}

int Scene::GetActiveCameraIndex() const
{
	return active_camera_index;
}

void Scene::SetActiveModelIndex(int index) 
{
	active_model_index = index;
}

int Scene::GetActiveModelIndex() const
{
	return active_model_index;
}
void Scene::Addlight(const shared_ptr<MeshModel>& light)
{
	lights.push_back(light);
}
int Scene::GetLightCount() const
{
	return lights.size();
}
MeshModel& Scene::GetLight(int index) const
{
	return *lights[index];
}
void Scene::RemoveLight(int index)
{
    if (index == lights.size() - 1)
        lights.pop_back();
    else {
        lights.erase(lights.begin() + index);
        lights.shrink_to_fit();
    }
 }
void Scene::SetWorldMat()
{
	world_mat = T*R*S;
}
void Scene::SetT(glm::mat4 k)
{
	T = k;
}
void Scene::SetS(glm::mat4 k)
{
	S = k;
}
void Scene::SetR(glm::mat4 k)
{
	R = k;
}
glm::mat4 Scene::GetWorldMat() const
{
	return world_mat;
}
//glm::mat4 Scene::CreatMatI(glm::vec4 k) {
//	glm::mat4 scalingMat;
//	for (int i = 0; i < 4; i++)
//		for (int j = 0; j < 4; j++)
//			if (i == j)
//				scalingMat[i][i] = k[i];
//			else
//				scalingMat[i][j] = 0;
//	return scalingMat;
//}
////creat translation matrix 
//// maybe i have to add z to this !!!!!!!!!!!!
//glm::mat4 Scene::Translate(float height, float width,float z ) const {
//	glm::mat4 translate = glm::mat4(1);
//	translate[0][3] = width;
//	translate[1][3] = height;
//	translate[2][3] = z;
//
//	return translate;
//}
/////scaling matrix based on the given parameters // requires translation after magnification
//glm::mat4 Scene::ScaleMat(float height = 1, float width = 1, float z = 1) {
//	return CreatMatI(glm::vec4(height, width, z, 1));
//}
///// rotation mat 0=x ,1=y,2=z 
//glm::mat4 Scene::RotateAxisk(int axis, float degree) {
//	glm::mat4 mat = CreatMatI();
//	glm::mat2x2 rotation = glm::mat2x2(glm::vec2(cos(M_PI * degree / 180), -sin(M_PI * degree / 180)), glm::vec2(sin(M_PI * degree / 180), cos(M_PI * degree / 180)));
//	int s = 0, k = 0;
//	for (int i = 0; i < 3; i++)
//	{
//		k = 0;
//		for (int j = 0; j < 3; j++) {
//
//			if (axis != i && axis != j)
//				mat[i][j] = rotation[s][k];
//			if (axis != j)
//				k++;
//		}
//		if (axis != i)
//			s++;
//	}
//	return mat;
//}

glm::mat4 Scene::object_mat(int modelnumber,bool lightOrMesh) const {
	MeshModel model = lightOrMesh?GetLight(modelnumber): GetModel(modelnumber);
	return glm::translate(glm::mat4(1), model.move)* glm::rotate(glm::mat4(1), (float)(model.Rotate.x), glm::vec3(1, 0, 0))* glm::rotate(glm::mat4(1), (float)(model.Rotate.y), glm::vec3(0, 1, 0))*
		glm::rotate(glm::mat4(1), (float)model.Rotate.z, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), model.scale);
	//return   glm::scale(glm::mat4(1), model.scale)* glm::rotate(glm::mat4(1), (float)(model .Rotate.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), (float)(model.Rotate.y), glm::vec3(0, 1, 0)) *
	//	glm::rotate(glm::mat4(1), (float)model.Rotate.z, glm::vec3(0, 0, 1)) *glm::translate(glm::mat4(1), model.move);
	//
}
glm::mat4 Scene::axisMat(int modelnumber) const{
	MeshModel model = GetActiveModel();
	return glm::translate(glm::mat4(1),model.move) * glm::scale(glm::mat4(1), model.scale);
	
}
GLuint Scene::GetVAO() const
{
    return Skyvao;
}
glm::mat4 Scene::World_mat(glm::vec3 move, glm::vec3 Rotate, glm::vec3 scale) {
	MeshModel model = GetActiveModel();
	return glm::translate(glm::mat4(1), move) * glm::rotate(glm::mat4(1), (float)(Rotate.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), (float)(Rotate.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1), (float)Rotate.z, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), scale);
	
}