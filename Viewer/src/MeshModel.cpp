#include "MeshModel.h"
int MeshModel::height = 1080;
int MeshModel::width = 1920;

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, std::vector<glm::vec2> textures, const std::string& model_name) :
	faces(faces),
	vertices(vertices),
	normals(normals) ,textures(textures){
	Translation = { 0,0,0,0 };
	T=S=R=model_mat = glm::mat4x4(1.f);
	
	Bounding = false;
	ortho = 1;
	material = light();
	FacesAdjecency = std::vector<std::vector<int>>(vertices.size(), std::vector<int>(0, 0));
	
	scale = glm::vec3(0.5, 0.5,0.5);
	move = glm::vec3(0, 0, 0);
	Rotate = glm::vec3(0, 0, 0);

	ReCalibrateParameters(height / 2.f, width / 2.f);
	modelver.reserve(3 * faces.size());
	for (int i = 0; i < faces.size(); i++)
	{
		Face currentFace = faces.at(i);
		for (int j = 0; j < 3; j++)
		{
			int vertexIndex = currentFace.GetVertexIndex(j) - 1;
			Vertex vertex;
			vertex.position = CorrectedVertices[vertexIndex];
			vertex.normal =CorrectedVertixNormals[vertexIndex];
/*might have to correct texture couardinates ! in recalibrate stuff ! ,normals might need correction 2 */
			if (textures.size() > 0)
			{
				int textureCoordsIndex = currentFace.GetTextureIndex(j) - 1;
				vertex.texture = textures[textureCoordsIndex];
			}

			modelver.push_back(vertex);
		}
	}
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, modelver.size() * sizeof(Vertex), &modelver[0], GL_STATIC_DRAW);

	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	// Vertex Texture Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	//cc  unbind to make sure other code does not change it somewhere else
	glBindVertexArray(0);


}
MeshModel::~MeshModel()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

const Face& MeshModel::GetFace(int index) const
{
	return faces[index];
}

int MeshModel::GetFacesCount() const
{
	return faces.size();
}

const std::string& MeshModel::GetModelName() const
{
	return model_name;
}

void MeshModel::SetVertixNormals() {
	glm::vec4 Avrage(0);
	std::vector<glm::vec4> Avr;
	for (int i = 0; i < GetFacesCount(); i++) {
		FacesAdjecency[(GetFace(i).GetVertexIndex(0) - 1)].push_back(i);
		FacesAdjecency[(GetFace(i).GetVertexIndex(1) - 1)].push_back(i);
		FacesAdjecency[(GetFace(i).GetVertexIndex(2) - 1)].push_back(i);
	}
	for (int i = 0; i < Getvectorsize(); i++) {
		Avrage = glm::vec4(0);
		for (int k = 0; k < FacesAdjecency[i].size(); k++) {
			Avrage += CorrectedFaceNormals[FacesAdjecency[i][k]];
		}
		Avrage =(Avrage / (float)FacesAdjecency[i].size()+CorrectedVertices[i])/2.f;
		//Avrage =(Avrage / (float)FacesAdjecency[i].size());
		
		/*Avrage = (Avrage + CorrectedVertices[i])/2.f;
		Avrage = (Avrage + CorrectedVertices[i])/2.f;*/
		CorrectedVertixNormals.push_back(Avrage );
	}
	
}

std::vector<glm::vec4> MeshModel::GetVertixNormals()
{
	return CorrectedVertixNormals;
}

void MeshModel::SetFaceBRecColor(){
	float r, g, b;
	for (int i = 0; i < GetFacesCount() ; i++) {
		r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
		FaceBRecColors.push_back({ r,g,b,1.f });
	}	
}

std::vector<glm::vec4> MeshModel::SetFaceNormals(std::vector<glm::vec4>& CorrectedVertices)
{
	glm::vec3 p1, p2, p3,p4;
	glm::vec4 normal,normal1,normal2, vertix,vertix1,vertix2 ;
	for (int i = 0; i <GetFacesCount(); i++) {
		vertix = CorrectedVertices[(GetFace(i).GetVertexIndex(0) - 1)] ;
		vertix1 = CorrectedVertices[(GetFace(i).GetVertexIndex(1) - 1)] ;
		vertix2 = CorrectedVertices[(GetFace(i).GetVertexIndex(2) - 1)] ;
		normal = (vertix1 - vertix);
		normal1 = (vertix2 - vertix);
		normal2 = glm::vec4(glm::normalize(cross(glm::vec3(normal),glm::vec3(normal1))),1);
		CorrectedFaceNormals.push_back(normal2);
		/*normal = (normal2 + (vertix1 + vertix2 + vertix) / 3.f) / 2.f;
		normal = (normal + (vertix1 + vertix2 + vertix) / 3.f) / 2.f;
		normal = (normal + (vertix1 + vertix2 + vertix) / 3.f) / 2.f;
		normal = (normal + (vertix1 + vertix2 + vertix) / 3.f) / 2.f;
		normal = (normal + (vertix1 + vertix2 + vertix) / 3.f) / 2.f;*/
		normal = (normal2 + (vertix1 + vertix2 + vertix) / 3.f)/2.f;
		normal = (normal2 + (vertix1 + vertix2 + vertix) / 3.f)/2.f;
		NormalsFromMidFace.push_back(normal) ;
		NormalsFromMidFace.push_back((vertix1 + vertix2 + vertix) /3.f) ;
	}
	return CorrectedVertices;
}

std::vector<glm::vec4>& MeshModel::GetFaceNormals()
{
	return CorrectedFaceNormals;
}

std::vector<glm::vec4>& MeshModel::GetFaceBRecColors()
{
	return FaceBRecColors;// TODO: insert return statement here
}

std::vector<glm::vec4>& MeshModel::GetMidFaceNormals()
{
	return NormalsFromMidFace;
}

std::vector<glm::vec4>& MeshModel::GetFCorrectedVertix()
{
	return CorrectedVertices;
}

//can be done in Renderer but that is a waste of precious rescorces 

void  MeshModel::ReCalibrateParameters(int halfheight,int halfwidth)
{

	glm::vec4 scal = findRatio(halfheight,halfwidth,0);
//recenter object around its axis!!
	std::vector<glm::vec4> vec;
	std::vector<float> pos;
	glm::vec4 k;
	for (int i = 0; i < vertices.size(); i++) {
		k.x =(scal.w / (2*halfwidth))*(vertices[i].x-scal.x);
		k.x = floorf(k.x * 10000) / 10000;
		k.y =(scal.w / (2 * halfwidth)) *( vertices[i].y- scal.y);
		k.y = floorf(k.y * 10000) / 10000;
		k.z = (scal.w / (2 * halfwidth)) *( vertices[i].z-scal.z);	
		k.z = floorf(k.z * 10000) / 10000;
		k.w = 1;
		CorrectedVertices.push_back(k);
	}
	//find new max min points 
	pos = findMaxMin(CorrectedVertices);
	SetBbox(pos);
	SetFaceNormals(CorrectedVertices);
	SetVertixNormals();
	SetFaceBRecColor();

	Translation = scal;
	
	

}
std::vector<glm::vec4> MeshModel::ModelAxis(float c) {
	std::vector<glm::vec4> vec;
		vec.push_back(glm::vec4(0, 0, 0, 1));
		vec.push_back(glm::vec4(c , 0, 0, 1));
		vec.push_back(glm::vec4(0, c , 0, 1));
		vec.push_back(glm::vec4(0, 0, c , 1));
		c = 0.5;
	return vec;
}
// here we find the ratio between the screen height/wedth to the max lenth of a courdinate in the givven victor .
glm::vec4 MeshModel::findRatio( int midheight, int midwidth,int swich)
{
	std::vector<glm::vec3> ver = vertices;
	height = 2 * midheight;
	width = 2 * midwidth;
	if (swich ==1)
		ver = normals;
	//might need swhich ==2 for texures in the future 
	float Xmax,Xmin , Ymax ,Ymin, Zmax,Zmin, safe_area,x,y,z;
		Xmax = Xmin=ver[0].x;
		Ymax = Ymin=ver[0].y;
		Zmax = Zmin=ver[0].z;
	for (int i = 0; i < ver.size(); i++) {
		Xmax = fmax(Xmax , ver[i].x);
		Xmin = fmin(Xmin , ver[i].x);
		Ymax = fmax( ver[i].y , Ymax);
		Ymin = fmin(Ymin, ver[i].y);
		Zmax = fmax( ver[i].z , Zmax);
		Zmin = fmin(Zmin, ver[i].z);
	}
	safe_area = midheight < midwidth ? midheight : midwidth;
	safe_area /= Ymax + abs(Ymin);
	x = (Xmax + Xmin) / 2;
	y = (Ymax +Ymin) / 2;
	z = (Zmax +Zmin) / 2;
	return glm::vec4 (x,y, z,(int)safe_area);
}


std::vector<float> MeshModel::findMaxMin( std::vector<glm::vec4> vec)
{
	std::vector<glm::vec4> ver = vec;
	std::vector<float> d;
	float Xmax,Xmin , Ymax ,Ymin, Zmax,Zmin;
		Xmax = Xmin=ver[0].x;
		Ymax = Ymin=ver[0].y;
		Zmax = Zmin=ver[0].z;
	for (int i = 0; i < vec.size(); i++) {
		Xmax = fmax(Xmax , ver[i].x);
		Ymax = fmax( ver[i].y , Ymax);
		Zmax = fmax( ver[i].z , Zmax);
		Xmin = fmin(Xmin, ver[i].x);
		Ymin = fmin(Ymin, ver[i].y);
		Zmin = fmin(Zmin, ver[i].z);
	}
	d.push_back(Xmax); d.push_back(Xmin); d.push_back(Ymax); d.push_back(Ymin); d.push_back(Zmax); d.push_back(Zmin);
	return d;
}

std::vector<float> MeshModel::findMaxMin( std::vector<glm::vec2> vec)
{
	std::vector<glm::vec2> ver = vec;
	std::vector<float> d;
	float Xmax, Xmin, Ymax, Ymin;
		Xmax = Xmin=ver[0].x;
		Ymax = Ymin=ver[0].y;
	
	for (int i = 0; i < vec.size(); i++) {
		Xmax = fmax(Xmax , ver[i].x);
		Ymax = fmax( ver[i].y , Ymax);
		Xmin = fmin(Xmin, ver[i].x);
		Ymin = fmin(Ymin, ver[i].y);
	}
	if (Xmax != Xmax || Xmin != Xmin || Ymax != Ymax || Ymin != Ymin)
		return d;
	else
	{
		d.push_back(Xmax); d.push_back(Xmin); d.push_back(Ymax); d.push_back(Ymin);
	}
	return d;
}

glm::vec4 MeshModel::GetTranslation()
{
	return Translation;
}

glm::ivec3 MeshModel::GetVector(int i)
{
	return vertices[i];
}

glm::vec4 MeshModel::GetVectorAsVec4(int i)
{
	return glm::vec4(vertices[i].x,vertices[i].y, vertices[i].z,1);
}

glm::mat4 MeshModel::GetLocalMat()
{
	return model_mat;
}

void MeshModel::SetBbox(std::vector<float> vec)
{
	for (int i = 0; i <2; i++)
		for (int k = 2; k < 4; k++)
			for (int z = 4; z < 6; z++)
				Bbox.push_back(glm::vec4(vec[i], vec[k], vec[z], 1));


	/**/
}

std::vector<glm::vec4>& MeshModel::GetBbox()
{
	return Bbox;
}

int MeshModel::Getvectorsize()
{
	return vertices.size();
}

glm::ivec2 MeshModel::GetHeightWidth()
{
	return glm::ivec2(height,width);
}

void MeshModel::SetHeightWidth(int height, int width)
{
	this->height = height;
	this->width = width;
}

void MeshModel::update_local()
{
	model_mat = T*R*S;
}

void MeshModel::update_T(glm::mat4 k)
{
	T = k;
}

void MeshModel::update_R(glm::mat4 k)
{
	R = k;
}

void MeshModel::update_S(glm::mat4 k)
{
	S = k;
}

GLuint MeshModel::GetVAO() const
{
	return vao;
}

light& MeshModel::Material()
{
	return material;
}

const std::vector<Vertex>& MeshModel::GetModelVertices()
{
	return modelver;
}

std::ostream& operator<<(std::ostream& o, MeshModel const& mesh)
{
	for (int i = 0; i < mesh.vertices.size(); i++) {
		o << "v ";
		o << std::to_string(mesh.vertices[i].x)+" "+ std::to_string(mesh.vertices[i].y)+" "+ std::to_string(mesh.vertices[i].z);
		o << std::endl;
	}
	for (int i = 0; i < mesh.GetFacesCount(); i++) {
		o << "f ";
		for (int j=0;j<3;j++)
			o << std::to_string(mesh.GetFace(i).GetVertexIndex(j)) + "//" + std::to_string(mesh.GetFace(i).GetNormalIndex(j)) + " ";
		o << std::endl;
	}
	return o;
}
