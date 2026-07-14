#include "DefaultScene.hpp"
#include "../Settings.hpp"

DefaultScene::DefaultScene() : SceneSkeleton(), m_view(ViewMode::FPS), m_assetManager(RE::AssetManager::instance())
{
	b3ShapeDef boxShapeDef = b3DefaultShapeDef();
	boxShapeDef.density = 2.0f;
	boxShapeDef.baseMaterial.friction = 0.1f;

	//Configure the shaders
	p_light = new RE::PointLight("../assets/shaders/blight.vs", "../assets/shaders/blight.fs", { -20, 15, 0 });
	p_lightRed = new RE::PointLight("../assets/shaders/blight.vs", "../assets/shaders/blight.fs", { -20, 13, -12 }, { 255, 0, 0 });
	p_dlight = new RE::DirectionalLight("../assets/shaders/lighting.vs", "../assets/shaders/lighting.fs", { -10, 10, 0 }, { 0, 0, 0 });

	//Load model, texture, shader, animation and configure assets
	m_assetManager.modele ["castle"]	= LoadModel("../assets/models/castle.obj");
	m_assetManager.modele ["robot"]		= LoadModel("../assets/models/robot.glb");
	m_assetManager.modele ["turret"]	= LoadModel("../assets/models/turret.obj");
	m_assetManager.texture["castle"]	= LoadTexture("../assets/textures/castle_diffuse.png");
	m_assetManager.texture["turret"]	= LoadTexture("../assets/textures/turret_diffuse.png");

	m_assetManager.shader ["light"]		= p_light;
	m_assetManager.shader ["lightRed"]	= p_lightRed;
	m_assetManager.shader["dlight"]		= p_dlight;

	m_assetManager.setModeleTexture( "castle", MATERIAL_MAP_DIFFUSE, m_assetManager.texture["castle"]);
	m_assetManager.setModeleTexture( "turret", MATERIAL_MAP_DIFFUSE, m_assetManager.texture["turret"]);

	m_assetManager.setMaterialShader("castle", p_dlight->shader);
	m_assetManager.setMaterialShader("robot",  p_light->shader);
	m_assetManager.setMaterialShader("turret", p_light->shader);

	m_assetManager.animator["robot"] = RE::Animator("../assets/models/robot.glb", &m_assetManager.modele["robot"]);

	//Setup game object
	m_castle.model = &m_assetManager.modele["castle"];
	m_castle.transform.position = { 40, 0, 0 };

	m_robot.model = &m_assetManager.modele["robot"];
	m_robot.transform.position = { 40, 0, 20 };
	m_robot.transform.rotation = b3MakeQuatFromAxisAngle({0, 1, 0}, -PI / 2);
	m_robot.transform.scale = { 0.05, 0.05, 0.05 };

	m_turret.model = &m_assetManager.modele["turret"];
	m_turret.transform.position = { 20, 0, -25 };

	//Setup physics game objects
	m_ground = RE::GameObject(world, { 0, -1, 0 }, b3Quat_identity, b3_staticBody);
	m_ground.loadModel(new Model(LoadModelFromMesh(GenMeshPlane(100, 100, 1, 1))), boxShapeDef, { 100, 0.1, 100 });
	m_ground.setShader(p_dlight->shader);

	m_cube1 = RE::GameObject(world, RE::transform_default, b3_dynamicBody);
	m_cube1.loadModel(new Model(LoadModelFromMesh(GenMeshCube(4, 4, 4))), boxShapeDef);
	m_cube1.setShader(p_dlight->shader);

	m_cube2 = RE::GameObject(world, RE::transform_default, b3_dynamicBody);
	m_cube2.loadModel(new Model(LoadModelFromMesh(GenMeshCube(4, 4, 4))), boxShapeDef);
	m_cube2.setShader(p_lightRed->shader);

	m_cube3 = RE::GameObject(world, RE::transform_default, b3_dynamicBody);
	m_cube3.loadModel(new Model(LoadModelFromMesh(GenMeshCube(5, 5, 5))), boxShapeDef, { 5, 5, 5 });
	m_cube3.setShader(p_lightRed->shader);
	
	m_cubeGroup.reserve(15);
	b3Vec3 cubeSize = { 2, 2, 2 };
	Model* miniCube = new Model(LoadModelFromMesh(GenMeshCube(cubeSize.x, cubeSize.y, cubeSize.z)));
	for (size_t i = 0; i < 15; i++)
	{	
		m_cubeGroup.emplace_back(RE::GameObject(world, { 0, cubeSize.y * i, 0 }, b3Quat_identity, b3_dynamicBody));
		m_cubeGroup[i].loadModel(miniCube, boxShapeDef);
		m_cubeGroup[i].setShader(p_lightRed->shader);
	}

	//Define key with actions
	RE::Input::instance().viewFPS.hold[KEY_E] = [&]() -> void {
		b3Body_ApplyLinearImpulseToCenter(m_cube3.id, { 0, 10, 0 }, true);
	};

	RE::Input::instance().viewFPS.hold[KEY_Q] = [&]() -> void {
		m_turret.transform.rotation = m_turret.transform.rotation * b3MakeQuatFromAxisAngle({ 0, 1, 0 }, GetFrameTime());
		m_castle.transform.rotation = m_castle.transform.rotation * b3MakeQuatFromAxisAngle({ 0, 1, 0 }, GetFrameTime());
	};

	//Init framebuffer for pixelised effect
	m_pixelised = RE::FrameBuffer(640, 360);
}

void DefaultScene::update()
{
	float dt = GetFrameTime();	
	if (!Settings::editMode)
	{
		m_view.update();
	}
		
	m_assetManager.animator["robot"].update();
	p_light->updateUniform();
	p_lightRed->updateUniform();
	p_dlight->updateUniform();

	//Physics
	b3World_Step(world, dt, Settings::subStepCount);
	m_cube1.updatePhysics();
	m_cube2.updatePhysics();
	m_cube3.updatePhysics();
	for (size_t i = 0; i < m_cubeGroup.size(); i++)
	{
		m_cubeGroup[i].updatePhysics();
	}
}

void DefaultScene::render()
{
	//Draw on the texture
	BeginTextureMode(m_pixelised.target);
		ClearBackground({ 40, 40, 40 });
		BeginMode3D(m_view.camera3D);
			m_castle.draw();
			m_robot.draw();
			m_turret.draw();
			m_cube1.draw();
			m_cube2.draw();
			m_cube3.draw();
			m_ground.draw();
			for (size_t i = 0; i < m_cubeGroup.size(); i++)
			{
				m_cubeGroup[i].draw();
			}
			
			p_dlight->draw();

			DrawLine3D({ 0, 0, 0 }, { 10, 0, 0 }, RED);
			DrawLine3D({ 0, 0, 0 }, { 0, 10, 0 }, GREEN);
			DrawLine3D({ 0, 0, 0 }, { 0, 0, 10 }, BLUE);
		EndMode3D();
	EndTextureMode();

	//Render texture
	ClearBackground({ 40, 40, 40 });
	m_pixelised.render();
}

void DefaultScene::gui()
{
	if (GuiButton({ 24, 24, 120, 30 }, "#158#Exit"))
	{
		exit(0);
	}

	ImGui::Begin("Settings");
		ImGui::Text("FPS : %i", GetFPS());		
		m_assetManager.shader["light"]->gui();
		m_assetManager.animator["robot"].gui();
		m_castle.gui();
		m_view.gui();
		ImGui::PushID(1);
		m_cube3.gui();
		ImGui::PopID();
		ImGui::SeparatorText("Directional light");
		ImGui::PushID(2);
		p_dlight->gui();
		ImGui::PopID();
	ImGui::End();
}