#define _USE_MATH_DEFINES
#include <cmath>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>
#include <iostream>
#include <sstream>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"
#include "Texture2D.h"


/**
 * Fields
 */
bool show_demo_window = true;
bool show_another_window = false;
bool blurrfilter = false;
bool bloom = false;
bool filters = false;
bool boxBlurr = false;
int windowWidth = 1280;
int windowHeight = 720;
static int nextMesh = 0;
static int nextlight = 0;
glm::vec4 clear_color = glm::vec4(0.4f, 0.4f, 0.4f, 1.00f);
glm::vec4 ModelColor = glm::vec4(0.5f, 0.5f, 0.5f, 1.00f);
glm::vec4 point_ambient = glm::vec4(1.00f, 1.00f, 1.00f, 1.00f);
glm::vec4 point_diffuse = glm::vec4(1.00f, 1.00f, 1.00f, 1.00f);
glm::vec4 point_specular = glm::vec4(1.00f, 1.00f, 1.00f, 1.00f);
glm::vec4 model_ambient = glm::vec4(133 / 255.00f, 19 / 255.00f, 19 / 255.00f, 1.00f);
glm::vec4 model_diffuse = glm::vec4(194 / 255.00f, 30 / 255.00f, 30 / 255.00f, 1.00f);
glm::vec4 model_specular = glm::vec4(1.00f, 1.00f, 1.00f, 1.00f);
/**
 * Function declarations
 */
static void GlfwErrorCallback(int error, const char* description);
void object_mat(int modelnumber, bool lightOrMesh,const Scene & scene) {
	MeshModel model = lightOrMesh ? scene.GetLight(modelnumber) : scene.GetModel(modelnumber);
	glm::translate(glm::mat4(1), model.move) * glm::rotate(glm::mat4(1), (float)(model.Rotate.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), (float)(model.Rotate.y), glm::vec3(0, 1, 0)) *
		glm::rotate(glm::mat4(1), (float)model.Rotate.z, glm::vec3(0, 0, 1)) * glm::scale(glm::mat4(1), model.scale);
	//return   glm::scale(glm::mat4(1), model.scale)* glm::rotate(glm::mat4(1), (float)(model .Rotate.x), glm::vec3(1, 0, 0)) * glm::rotate(glm::mat4(1), (float)(model.Rotate.y), glm::vec3(0, 1, 0)) *
	//	glm::rotate(glm::mat4(1), (float)model.Rotate.z, glm::vec3(0, 0, 1)) *glm::translate(glm::mat4(1), model.move);
	//
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);

ImGuiIO& SetupDearImgui(GLFWwindow* window);

void StartFrame();

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);

void Cleanup(GLFWwindow* window);

void DrawImguiMenus(ImGuiIO& io, Scene& scene, Renderer& renderer);
void glfw_OnFramebufferSize(GLFWwindow* window, int width, int height);

/**
 * Function implementation
 */
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);

	
}



int main(int argc, char **argv)
{
	int windowWidth = 2560, windowHeight = 1440;
	string out;
	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer");
	if (!window)
		return 1;
	glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
	glEnable(GL_DEPTH_TEST);
	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	//read and print the meshmodel	 

	Renderer renderer(frameBufferWidth, frameBufferHeight);
	Scene scene = Scene();
	
	shared_ptr<MeshModel> model = Utils::LoadMeshModel("..\\Data\\teapot.obj");
	shared_ptr<Camera> a= make_shared<Camera>();
	scene.AddCamera(a);

	scene.AddModel(model);
	scene.SetActiveModelIndex(nextMesh++);
	ImGuiIO& io = SetupDearImgui(window);
	glfwSetScrollCallback(window, ScrollCallback);

	renderer.LoadShaders();
	renderer.LoadTextures();
	renderer.loadCubeMap();

    while (!glfwWindowShouldClose(window))
    {
		glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
        glfwPollEvents();
		StartFrame();
		DrawImguiMenus(io, scene,renderer);
		RenderFrame(window, scene, renderer, io);
		
		
    }

	Cleanup(window);
    return 0;
}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	#if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	
	GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
						 // very importent!! initialization of glad
						 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped
	//glfwSetFramebufferSizeCallback(window, glfw_OnFramebufferSize);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return window;
}
// ---------------------------------------------------------------------------- -
// Is called when the window is resized
//-----------------------------------------------------------------------------
void glfw_OnFramebufferSize(GLFWwindow * window, int width, int height)
{
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, windowWidth, windowHeight);
	//scene->GetActiveCamera().SetAspectRatio(GetAspectRatio());
}
ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return io;
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
{			
	
	
	
	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	glm::vec4 r = scene.GetActiveCamera().GetProjectionTransformation() * glm::vec4(1);
	static float x=0, y=0;
	if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
	{
		if (frameBufferWidth > 0 && frameBufferHeight > 0)
		{
			renderer.SetWidthHeight(frameBufferHeight, frameBufferWidth);
			scene.GetActiveModel().SetHeightWidth(frameBufferHeight, frameBufferWidth);
			renderer.ViewportChanged = true;
			glViewport(0, 0, frameBufferWidth, frameBufferHeight);
		}
		

	}
	if (scene.point&&!io.WantCaptureMouse) {
		if (io.MouseDown[0])
		{
			
			x = (io.MouseClickedPos[0].x);
			y = (frameBufferHeight -io.MouseClickedPos[0].y);
			x = ((1 / r.x) * (io.MouseClickedPos[0].x - renderer.GetViewportWidth() / 2) / (renderer.GetViewportWidth() / 2.f));
			y = ((1 / r.y) * (renderer.GetViewportHeight() / 2 - io.MouseClickedPos[0].y) / (renderer.GetViewportHeight() / 2.f));
			shared_ptr<MeshModel> lights = Utils::LoadMeshModel("..\\Data\\golfBall.obj");
			lights->Material().SetPosition(glm::vec3(x, y, 0));
			lights->move=glm::vec3(x, y, 0);
			lights->scale = glm::vec3(0.1, 0.1, 0.1);
			scene.Addlight(lights);
			scene.GetLight(nextlight).update_S(glm::scale(glm::mat4(1), lights->scale));
			scene.GetLight(nextlight).update_local();
			nextlight++;
			scene.point = false;
		}
	}
	if (!io.WantCaptureKeyboard)
	{
		// TODO: Handle keyboard events here
		/*for (int i = 0; i < 5; i++)
			cout << io.MouseClickedPos[i].x << "  " << io.MouseClickedPos[i].y << endl;*/
		// m key is down
		if (io.KeyAlt)
		{
			if (!io.WantCaptureMouse) {
				if (io.MouseDown[0])
				{
				
					scene.GetActiveModel().move.x = (1/r.x)*(io.MouseClickedPos[0].x - renderer.GetViewportWidth() / 2)/ (renderer.GetViewportWidth()/2.f);
					scene.GetActiveModel().move.y = (1/r.y)* (renderer.GetViewportHeight() / 2 - io.MouseClickedPos[0].y) / (renderer.GetViewportHeight()/2.f);
				}	
			}
		
			if (io.KeysDown[87])
				scene.wRotate.x--;
			if (io.KeysDown[83])
				scene.wRotate.x++;
			if (io.KeysDown[65])
				scene.wRotate.y++;
			if (io.KeysDown[68])
				scene.wRotate.y--;
			if (io.KeysDown[69])
				scene.wRotate.z++;
			if (io.KeysDown[81])
				scene.wRotate.z--;

		}

		if (io.KeyCtrl)
		{
			
			if (!io.WantCaptureMouse) {
				if (io.MouseDown[0])
				{
					scene.wmove.x = (1 / r.x) * (io.MouseClickedPos[0].x - renderer.GetViewportWidth() / 2) / (renderer.GetViewportWidth() / 2.f);
					scene.wmove.y = (1 / r.y) * (renderer.GetViewportHeight() / 2 - io.MouseClickedPos[0].y) / (renderer.GetViewportHeight() / 2.f);
				}
				
			}
			if (io.KeysDown[87])
				scene.GetActiveModel().Rotate.x--;
			if (io.KeysDown[83])
				scene.GetActiveModel().Rotate.x++;
			if (io.KeysDown[65])
				scene.GetActiveModel().Rotate.y++;
			if (io.KeysDown[68])
				scene.GetActiveModel().Rotate.y--;
			if (io.KeysDown[69])
					scene.GetActiveModel().Rotate.z++;
			if (io.KeysDown[81])
				scene.GetActiveModel().Rotate.z--;

		}
		
		//W,A,S,D  work as up,left,down,right 
		

		


	}
	
	ImGui::Render();
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderer.Render(scene);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	

	
	
	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
}

void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}
// have to update camera trans' and light transformations ! basically every thing else is done 
void DrawImguiMenus(ImGuiIO& io, Scene& scene,Renderer& renderer)
{
	/**
	 * MeshViewer menu
	 */
	 	static bool CameraControls = false, Bbox = false, uni = false, wuni = false, Cam, LightSource = false;
	 	static int lights = 0,mode=0;
	 	static float  uniformscale = 1, wuniformscale = 1, viewport = 1, intinsity, pos2[3],theta=0,gamma=90,SphereTheta=0,SpherePhi=0,
	 		l = -(float)Renderer::GetViewportWidth() / Renderer::GetViewportHeight(),
	 		r = (float)Renderer::GetViewportWidth() / Renderer::GetViewportHeight(), t = 1, b = -1, Distance = 10, l2, r2;
	 	static glm::vec3 CLtranlate(0), CLrotate(0), CLscale(1), CWtranlate(0), CWrotate(0), Wrotate(0), Wtranslate(0), lightpos(0), objmove(0), move(0), ROT(0), SCAL(1);
		static bool objectControl = false;
		static glm::vec4 coard = scene.GetActiveCamera().GetProjectionTransformation() * glm::vec4(1);
		const char* modes[3] = {"use mirroring with poles up ","poles around z axis ","poles around y axis (up)"};
		ImGuiWindowFlags windows = 0;
		windows |= ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoBackground;
		static int k = Renderer::GetViewportHeight(),modelNum=0;
		static int c = scene.GetActiveModel().GetHeightWidth().y;
		ImGui::GetStyle().TabRounding = 0.1;
		ImGui::GetStyle().WindowRounding = 20;
		ImGui::GetStyle().FrameRounding = 20;
		ImGui::GetStyle().Colors[ImGuiCol_TabActive] = ImVec4(0, 0, 0.6, 1);
		ImGui::GetStyle().Colors[ImGuiCol_Tab] = ImVec4(0.5, 0.5, 0.5, 1);
		ImGui::GetStyle().Colors[ImGuiCol_Border] = ImVec4(0.5, 0, 0, 1);
		if (Renderer::GetViewportHeight() != 0)
			viewport = Renderer::GetViewportHeight();
		else
			viewport = 1;
		if (Renderer::ViewportChanged) {
			l = -(float)Renderer::GetViewportWidth() / viewport;
			r = (float)Renderer::GetViewportWidth() / viewport;
			t = 1; b = -1;
			Renderer::ViewportChanged = false;
		}
		int currentmode=0;
		const char* scenePr[3] = { "enviroment mode " ,"fill triangles " ,"wirframe"};
		std::vector<std::string> cameraStrings;
		ImGui::Begin("Main menu", &objectControl,windows);
			ImGui::BeginTabBar("tabs");
			if (ImGui::BeginTabItem("main")) {
				ImGui::Text("Camera and transformations window and thier colors");
				if (ImGui::ColorEdit3("world color", (float*)&clear_color)) // Edit 3 floats representing a color
					glClearColor(clear_color.r, clear_color.g, clear_color.b, clear_color.a);
				if (ImGui::ColorEdit3("Model color", (float*)&ModelColor)) // Edit 3 floats representing a color
					scene.Objcolor = ModelColor;
				ImGui::Combo("projection type ", &Scene::mode, scenePr, 3);
				ImGui::Checkbox("Textures on/off ", &scene.textures);
				ImGui::SameLine();
				ImGui::Checkbox("Spherical textures ", &Renderer::IsSpherical);
				ImGui::Separator();
				ImGui::Checkbox("Refract in enviroment mapping ", &Renderer::Refract);
				ImGui::InputFloat("refraction: enviroment mapping ratio ", &Renderer::ratio, 0.05, 0.2, 2);
				ImGui::Separator();
				ImGui::Checkbox("Transformations", &objectControl);
				ImGui::SameLine();
				ImGui::Checkbox("Camera And Fov", &CameraControls);

				//ImGui::Checkbox("blurr scene", &filters);
				ImGui::Separator();
				//ImGui::Text("Controle bounding box and Bounding Rectangles");
				//ImGui::ColorEdit3("Bounding box colors", (float*)&scene.BboxColor); // Edit 3 floats representing a color
				//ImGui::Checkbox("bounding box ", &Bbox);
				//ImGui::Checkbox("Bounding Rectangles ", &scene.show_BRec);
				//ImGui::Separator();
				//ImGui::Text("Controle Normals");
				//ImGui::ColorEdit3("Vertix normal colors", (float*)&scene.PerVertixColor); // Edit 3 floats representing a color
				//ImGui::ColorEdit3("Face normals colors", (float*)&scene.PerFaceColor); // Edit 3 floats representing a color
				//ImGui::Checkbox("Normals Per Face ", &Scene::PerFace);
				//ImGui::Checkbox("Normals Per vertix ", &Scene::PerVertix);
				//ImGui::Separator();
				//ImGui::Text("Control axis visability");
				//ImGui::Checkbox("object axis", &Scene::show_obj_axis);
				//ImGui::SameLine();
				//ImGui::Checkbox("world axis", &Scene::show_axis);
				//ImGui::Checkbox("snap axis", &Scene::snap);
				//ImGui::Separator();
				ImGui::Text("Control light source");
				ImGui::Checkbox("Add a point", &Scene::point);
				ImGui::Checkbox("let light affect scene ", &Renderer::light_on);
				ImGui::Checkbox("light controls", &LightSource);
				scene.GetActiveModel().Bounding = Bbox;
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				ImGui::EndTabItem();
			}
			if (Renderer::IsSpherical && ImGui::BeginTabItem("spherical texture manipulations")) {
				ImGui::InputFloat("Phi", &SpherePhi, 0.05, 0.2, 2);
				ImGui::InputFloat("Theta ", &SphereTheta, 0.05, 0.2, 2);
				ImGui::Combo("select mode ", &Renderer::type_sphere, modes, 3);
				Renderer::deltaTheta = glm::radians(SphereTheta);
				Renderer::deltaPhi = glm::radians(SpherePhi);
				ImGui::EndTabItem();
			}
			if (objectControl && ImGui::BeginTabItem("Object Controls")) {
				const char** ModelPr = new const char* [scene.GetModelCount()];
				std::vector<std::string> Modelstr;
				for (int i = 0; i < scene.GetModelCount(); i++)
				{
					std::ostringstream str;
					str <<"#"<<i<<" "<<scene.GetModel(i).GetModelName();
					Modelstr.push_back(str.str());
				}
				for (int i = 0; i < scene.GetModelCount(); i++)
					ModelPr[i] = Modelstr[i].c_str();

				if (ImGui::Combo("select Model ", &modelNum, ModelPr, scene.GetModelCount()))
					scene.SetActiveModelIndex(modelNum);
				ImGui::Text("These are transformations on the object");
				ImGui::Separator();
				ImGui::Text("Move/Translate ");                          // Buttons return true when clicked (most widgets return true when edited/activated)	
				ImGui::SliderFloat2("Move on x axis ", &move.x, l, r);
				ImGui::SliderFloat("Move on z axis ", &move.z, scene.GetActiveCamera().n, scene.GetActiveCamera().f);
				ImGui::Separator();
				if (ImGui::Button("Uniform Scaling"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
					SCAL.x = SCAL.y = SCAL.z = scene.uniform.x;
				ImGui::SliderFloat("widen or tighten", &scene.uniform.x, 0.0f, 2.0f);
				ImGui::Separator();
				ImGui::SliderFloat3("scale x,y,z", &SCAL.x, 0.0f, 1.0f);
				ImGui::Separator();
				ImGui::SliderAngle("Rotate  x", &ROT.x, -359, 359);            // rotate
				ImGui::SliderAngle("Rotate  y", &ROT.y, -359, 359);            // rotate
				ImGui::SliderAngle("Rotate  z", &ROT.z, -359, 359);            // rotate
				ImGui::Text("These are transformations on the world");
				ImGui::SliderAngle("rotate  x ", &scene.wRotate.x, -359, 359);            // rotate
				ImGui::SliderAngle("rotate  y ", &scene.wRotate.y, -359, 359);            // rotate
				ImGui::SliderAngle("rotate  z ", &scene.wRotate.z, -359, 359);            // rotate           // rotate
				ImGui::Separator();
				ImGui::Text("move/Translate ");                          // Buttons return true when clicked (most widgets return true when edited/activated)	
				ImGui::SliderFloat2("moove x axis   y", &scene.wmove.x, l, r);
				ImGui::SliderFloat("move z axis ", &scene.wmove.z, scene.GetActiveCamera().n, scene.GetActiveCamera().f);
				if (ImGui::Button("revert all to origin ")) {
					scene.wRotate=ROT = glm::vec3(0);
					move=scene.wmove = glm::vec3(0);
					scene.uniform.x = SCAL.x = SCAL.y = SCAL.z = 1;
				}
				ImGui::EndTabItem();
			}
			if (CameraControls && ImGui::BeginTabItem("Camera")) {
				ImGui::Text("These are transformations on the camera");
				ImGui::Checkbox("Camera Transformations ", &Cam);
				ImGui::Text("perspective =flase ,ortho=true");                          // Buttons return true when clicked (most widgets return true when edited/activated)	
				ImGui::Checkbox("perspective/orthographic projection ", &Scene::pers_ortho);
				ImGui::SliderFloat("rotate Camera vertically", &theta, -90.0f, 90.0f);
				ImGui::SliderFloat("rotate Camera horizontally", &gamma, -360.0f, 360.0f);
				scene.GetActiveCamera().eye.x = cos(glm::radians(gamma)) * cos(glm::radians(theta));
				scene.GetActiveCamera().eye.y = sin(glm::radians(theta));
				scene.GetActiveCamera().eye.z = sin(glm::radians(gamma)) * cos(glm::radians(theta));
				if (Scene::pers_ortho)
					ImGui::SliderFloat("Orthogonal width", &scene.GetActiveCamera().TOrtho, 0.0f, 100.0f);
				else
					ImGui::SliderAngle("Perspective width", &scene.GetActiveCamera().Tperspective, 1.f, 160.0f);
				scene.GetActiveModel().ortho = scene.GetActiveCamera().TOrtho;
				ImGui::Separator();
				ImGui::PushItemWidth(60);
				ImGui::SliderFloat("left", &l, -1.0f, 1.0f);
				ImGui::SameLine();
				ImGui::SliderFloat("right", &r, -1.0f, 1.0f);
				ImGui::Separator();
				ImGui::SliderFloat("bottom", &b, -1.0f, 1.0f);
				ImGui::SameLine();
				ImGui::SliderFloat("top", &t, -1.0f, 1.0f);
				ImGui::Separator();
				ImGui::SliderFloat("near", &scene.GetActiveCamera().n, -1.0f, 1.0f);
				ImGui::SameLine();
				ImGui::SliderFloat("far", &scene.GetActiveCamera().f, -1.0f, 1.0f);
				if (!Scene::pers_ortho) {
					l = -(float)Renderer::GetViewportWidth() / viewport;
					r = (float)Renderer::GetViewportWidth() / viewport;
					t = 1; b = -1;
				}
				ImGui::Separator();
				ImGui::PushItemWidth(90);
				ImGui::InputFloat("Move camera x", &scene.GetActiveCamera().eye.x, 0.1, 0.5, 2, 1);
				ImGui::SameLine();
				ImGui::InputFloat("Move camera y", &scene.GetActiveCamera().eye.y, 0.1, 0.5, 2, 1);
				ImGui::SameLine();
				ImGui::InputFloat("Move camera z", &scene.GetActiveCamera().eye.z, 0.1, 0.5, 2, 1);
				ImGui::EndTabItem();
			}
			
			if (Cam && ImGui::BeginTabItem("Camera Transformations")) {
				ImGui::Text("These are transformations on the object");
				ImGui::Separator();
				ImGui::Text("move/Translate ");                          // Buttons return true when clicked (most widgets return true when edited/activated)	
				ImGui::SliderFloat2("Move on x axis ", &CLtranlate.x, l, r);
				ImGui::SliderFloat("Move on z axis ", &CLtranlate.z, scene.GetActiveCamera().n, scene.GetActiveCamera().f);
				ImGui::Separator();
				ImGui::SliderAngle("Rotate x", &CLrotate.x, -359, 359);            // rotate
				ImGui::SliderAngle("Rotate y", &CLrotate.y, -359, 359);            // rotate
				ImGui::SliderAngle("Rotate z", &CLrotate.z, -359, 359);            // rotate
				ImGui::Text("These are transformations on the world");
				ImGui::Text("move/translate ");                          // Buttons return true when clicked (most widgets return true when edited/activated)	
				ImGui::SliderFloat2("moove on x axis, y ", &CWtranlate.x, l, r);
				ImGui::SliderFloat("moove on z axis ", &CWtranlate.z, scene.GetActiveCamera().n, scene.GetActiveCamera().f);
				ImGui::Separator();
				ImGui::Text("Rotate ");                          // Buttons return true when clicked (most widgets return true when edited/activated)	
				ImGui::SliderAngle("rotate x ", &CWrotate.x, -359, 359);            // rotate
				ImGui::SliderAngle("rotate y ", &CWrotate.y, -359, 359);            // rotate
				ImGui::SliderAngle("rotate z ", &CWrotate.z, -359, 359);            // rotate           // rotate
				ImGui::Separator();
				if (ImGui::Button("revert all to origin ")) {
					CLtranlate = glm::vec3(0);
					CLrotate = glm::vec3(0);
					CWtranlate = glm::vec3(0);
					CWrotate = glm::vec3(0);
				}
				ImGui::EndTabItem();
				scene.GetActiveCamera().SetLocal(CLtranlate, CLrotate, glm::vec3(1));
				scene.GetActiveCamera().SetWorld(CWtranlate, CWrotate, glm::vec3(1));
			}
		/*	if (filters && ImGui::BeginTabItem("after effects")) {
				ImGui::Checkbox("blurr", &blurrfilter);
				ImGui::Checkbox("Box blurr", &boxBlurr);
				ImGui::Checkbox("bloom", &bloom);
				ImGui::InputFloat("blurrig factor", &scene.sigma, 0.05, 0.2, 2);
				ImGui::ColorEdit3("point ambient", (float*)&bloomThreshhold);
				ImGui::EndTabItem();
			}*/
			
			if (LightSource && scene.GetLightCount() && ImGui::BeginTabItem("light and material")) {
				glm::vec3 pos;
				ImGui::Text("controls for light position and material colors");
				/*ImGui::Checkbox("show Point ", &Scene::showpoint);
				ImGui::Checkbox("Flat Shading ", &Scene::flat);*/
				ImGui::ColorEdit3("point ambient", (float*)&point_ambient);
				ImGui::ColorEdit3("point diffuse", (float*)&point_diffuse);
				ImGui::ColorEdit3("point specular", (float*)&point_specular);
				scene.GetActiveModel().Material().SetAmbient(point_ambient);
				scene.GetActiveModel().Material().SetSpecular(point_specular);
				scene.GetActiveModel().Material().SetDiffuse(point_diffuse);
				ImGui::ColorEdit3("model ambient", (float*)&model_ambient);
				ImGui::ColorEdit3("model diffuse", (float*)&model_diffuse);
				ImGui::ColorEdit3("model specular", (float*)&model_specular);
				ImGui::Separator();
				ImGui::Text("light position controles");

				/*if (scene.GetLightCount()>0)*/const char** scenePr = new const char* [scene.GetLightCount()];
				std::vector<std::string> lightstr;
				for (int i = 0; i < scene.GetLightCount(); i++)
				{
					std::ostringstream str;
					str << "light # " << i;
					lightstr.push_back(str.str());
				}
				for (int i = 0; i < scene.GetLightCount(); i++)
					scenePr[i] = lightstr[i].c_str();

				if (ImGui::Combo("select light ", &lights, scenePr, scene.GetLightCount()))
				{
					point_ambient = glm::vec4(scene.GetLight(lights).Material().GetAmbient(), 1.f);
					point_diffuse = glm::vec4(scene.GetLight(lights).Material().GetDiffuse(), 1.f);
					point_specular = glm::vec4(scene.GetLight(lights).Material().GetSpecular(), 1.f);
				}
				//ImGui::ArrowButton("what", 0);
				
				/*if (scene.GetLightCount()>0)*/
					delete[] scenePr;
				lightpos = scene.GetLight(lights).move;
				ImGui::PushItemWidth(90);
				if (ImGui::InputFloat("move x", &lightpos.x, 0.05, 0.1, 3)) { scene.GetLight(lights).move = lightpos; }
				ImGui::SameLine();
				if (ImGui::InputFloat("move y", &lightpos.y, 0.05, 0.1, 3)) { scene.GetLight(lights).move = lightpos; }
				ImGui::SameLine();
				if (ImGui::InputFloat("move z", &lightpos.z, 0.05, 0.1, 3)) { scene.GetLight(lights).move = lightpos; }
				if (ImGui::InputFloat("intensity", &intinsity, 0.05, 0.1, 3)) { scene.GetLight(lights).Material().SetIntensity(intinsity); }
				if (ImGui::Checkbox("Show reflected ray", &scene.showrays)) {}
				scene.GetLight(lights).Material().SetAmbient(model_ambient);
				scene.GetLight(lights).Material().SetDiffuse(model_diffuse);
				scene.GetLight(lights).Material().SetSpecular(model_specular);
				scene.GetLight(lights).update_T(glm::translate(glm::mat4(1), lightpos));
				scene.GetLight(lights).update_local();
				if (ImGui::Button("remove selected light") && scene.GetLightCount()) {
					cout << nextlight << endl;
					scene.RemoveLight(lights);
					lights--;
					nextlight--;
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
			
		ImGui::End();
		    scene.GetActiveModel().update_T(glm::translate(glm::mat4(1), move));
			scene.GetActiveModel().update_R(glm::rotate(glm::mat4(1), (float)(ROT.x), glm::vec3(1, 0, 0))* glm::rotate(glm::mat4(1), (float)(ROT.y), glm::vec3(0, 1, 0))*glm::rotate(glm::mat4(1), (float)ROT.z, glm::vec3(0, 0, 1)));
			scene.GetActiveModel().update_S(glm::scale(glm::mat4(1), SCAL));
			scene.GetActiveModel().update_local();
			scene.SetT(glm::translate(glm::mat4(1), scene.wmove));
			scene.SetR(glm::rotate(glm::mat4(1), (float)(scene.wRotate.x), glm::vec3(1, 0, 0))* glm::rotate(glm::mat4(1), (float)(scene.wRotate.y), glm::vec3(0, 1, 0))* glm::rotate(glm::mat4(1), (float)scene.wRotate.z, glm::vec3(0, 0, 1)));
			scene.SetWorldMat();
			scene.GetActiveCamera().l = l / scene.GetActiveCamera().TOrtho * 20;
			scene.GetActiveCamera().r = r / scene.GetActiveCamera().TOrtho * 20;
			scene.GetActiveCamera().t = t / scene.GetActiveCamera().TOrtho * 20;
			scene.GetActiveCamera().b = b / scene.GetActiveCamera().TOrtho * 20;
			scene.GetActiveCamera().SetViewTrans(Scene::pers_ortho, Renderer::GetViewportWidth() / viewport);
		
	// Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Add Model", "CTRL+M"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					shared_ptr<MeshModel> model = Utils::LoadMeshModel(outPath);
					// model->ReCalibrateParameters(scene.GetModel(0).GetHeightWidth().x/2, scene.GetModel(0).GetHeightWidth().y / 2);
					scene.AddModel(model);
					scene.SetActiveModelIndex(nextMesh++);
		
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("texture"))
		{
			if (ImGui::MenuItem("Open 2D texure", "CTRL+T"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("png;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					renderer.LoadTextures(outPath);
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			if (ImGui::MenuItem("Open Cubic texure", "CTRL+C"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("png;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			ImGui::EndMenu();
		}

		// TODO: Add more menubar items (if you want to)
		ImGui::EndMainMenuBar();
	}

	// Controls
	/*ImGui::ColorEdit3("Clear Color", (float*)&clear_color);*/
	// TODO: Add more controls as needed


	/**
	 * Imgui demo - you can remove it once you are familiar with imgui
	 */

	 // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	/*if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);*/

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	
	

	// 3. Show another simple window.
	//if (show_another_window)
	//{
	//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
	//	ImGui::Text("Hello from another window!");
	//	if (ImGui::Button("Close Me"))
	//		show_another_window = false;
	//	ImGui::End();
	//}
}