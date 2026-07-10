#include "DefaultScene.hpp"
#include "../Settings.hpp"

DefaultScene::DefaultScene() : m_view(ViewMode::FPS), m_assetManager(AssetManager::instance())
{
	//Create world
	b3WorldDef worldDef = b3DefaultWorldDef();
	worldDef.gravity = Settings::g;
	m_worldID = b3CreateWorld(&worldDef);

	//Create ground by putting a boxhull with body def (static by default)
	b3BodyDef groundBodyDef = b3DefaultBodyDef();
	groundBodyDef.position = { 0, -10, 0 };
	m_groundID = b3CreateBody(m_worldID, &groundBodyDef);
	
	b3BoxHull box = b3MakeBoxHull(50, 10, 50);
	b3ShapeDef shapeDef = b3DefaultShapeDef();
	b3CreateHullShape(m_groundID, &shapeDef, &box.base);

	//Create dynamic body box
	b3BodyDef bodyDef = b3DefaultBodyDef();
	bodyDef.type = b3_dynamicBody;
	bodyDef.position = { 0, 4, 0 };
	m_bodyID1 = b3CreateBody(m_worldID, &bodyDef);

	bodyDef.position = { 1, 10, 0 };
	m_bodyID2 = b3CreateBody(m_worldID, &bodyDef);

	b3BoxHull dynamicBox = b3MakeCubeHull(2.0f);
	b3ShapeDef boxShapeDef = b3DefaultShapeDef();
	boxShapeDef.density = 2.0f;
	boxShapeDef.baseMaterial.friction = 0.1f;
	b3CreateHullShape(m_bodyID1, &boxShapeDef, &dynamicBox.base);
	b3CreateHullShape(m_bodyID2, &boxShapeDef, &dynamicBox.base);

	//Configure the shaders
	Light* light = new Light("../assets/shaders/light.vs", "../assets/shaders/light.fs");
	light->position = { -20, 0, 0 };

	Light* lightRed = new Light("../assets/shaders/light.vs", "../assets/shaders/light.fs");
	lightRed->position = { -20, 13, -12 };
	lightRed->color = { 1, 0, 0 };

	//Load model, texture, shader, animation and configure assets
	m_assetManager.modele ["castle"]	= LoadModel("../assets/models/castle.obj");
	m_assetManager.modele ["robot"]		= LoadModel("../assets/models/robot.glb");
	m_assetManager.modele ["turret"]	= LoadModel("../assets/models/turret.obj");
	m_assetManager.texture["castle"]	= LoadTexture("../assets/textures/castle_diffuse.png");
	m_assetManager.texture["turret"]	= LoadTexture("../assets/textures/turret_diffuse.png");
	m_assetManager.shader ["light"]		= light;
	m_assetManager.shader["lightRed"]	= lightRed;

	m_assetManager.setModeleTexture( "castle", MATERIAL_MAP_DIFFUSE, m_assetManager.texture["castle"]);
	m_assetManager.setModeleTexture( "turret", MATERIAL_MAP_DIFFUSE, m_assetManager.texture["turret"]);
	m_assetManager.setMaterialShader("castle", m_assetManager.shader["light"]->shader);
	m_assetManager.setMaterialShader("robot",  m_assetManager.shader["light"]->shader);
	m_assetManager.setMaterialShader("turret", m_assetManager.shader["lightRed"]->shader);

	m_assetManager.animator["robot"] = Animator("../assets/models/robot.glb", &m_assetManager.modele["robot"]);

	//Setup game object
	m_castle.model = &m_assetManager.modele["castle"];
	m_castle.transform.translation = { 40, 0, 0 };

	m_robot.model = &m_assetManager.modele["robot"];
	m_robot.transform.translation = { 40, 0, 20 };
	m_robot.transform.rotation = { 0, -PI / 2, 0 };
	m_robot.transform.scale = { 0.05, 0.05, 0.05 };

	m_turret.model = &m_assetManager.modele["turret"];
	m_turret.transform.translation = { 20, 0, -25 };
	m_turret.transform.rotation = { 0, 0, 0 };

	m_cube1.model = new Model(LoadModelFromMesh(GenMeshCube(4.0f, 4.0f, 4.0f)));
	m_cube2.model = new Model(LoadModelFromMesh(GenMeshCube(4.0f, 4.0f, 4.0f)));
	m_cube1.model->materials[0].shader = m_assetManager.shader["lightRed"]->shader;
	m_cube2.model->materials[0].shader = m_assetManager.shader["lightRed"]->shader;

	m_ground.model = new Model(LoadModelFromMesh(GenMeshPlane(100, 100, 1, 1)));
	m_ground.model->materials[0].shader = m_assetManager.shader["light"]->shader;
	m_ground.transform.translation = { 0, 0, 0 };

	//Define key with actions
	Input::instance().viewFPS.hold[KEY_E] = [&]() -> void {
		b3Body_ApplyLinearImpulseToCenter(m_bodyID1, { 0, 10, 0 }, true);
	};
}

void DefaultScene::update()
{
	float dt = GetFrameTime();
	if (!Settings::editMode)
	{
		m_view.update();
	}
		
	m_assetManager.shader["light"]->updateUniform();
	m_assetManager.shader["lightRed"]->updateUniform();
	m_assetManager.animator["robot"].update();

	//Physics
	b3World_Step(m_worldID, dt, Settings::subStepCount);
	b3Vec3 p1 = b3Body_GetPosition(m_bodyID1);
	b3Quat r1 = b3Body_GetRotation(m_bodyID1);
	m_cube1.transform.translation = { p1.x, p1.y, p1.z };
	m_cube1.transform.rotation = { r1.v.x, r1.v.y, r1.v.z, r1.s };

	b3Vec3 p2 = b3Body_GetPosition(m_bodyID2);
	b3Quat r2 = b3Body_GetRotation(m_bodyID2);
	m_cube2.transform.translation = { p2.x, p2.y, p2.z };
	m_cube2.transform.rotation = { r2.v.x, r2.v.y, r2.v.z, r2.s };
}

void DefaultScene::render()
{
	ClearBackground({ 30, 30, 30 });

	BeginMode3D(m_view.camera3D);	
		m_castle.draw();
		m_robot.draw();
		m_turret.draw();
		m_cube1.draw();
		m_cube2.draw();
		m_ground.draw();
		DrawLine3D({ 0, 0, 0 }, { 10, 0, 0 }, RED);
		DrawLine3D({ 0, 0, 0 }, { 0, 10, 0 }, GREEN);
		DrawLine3D({ 0, 0, 0 }, { 0, 0, 10 }, BLUE);
	EndMode3D();
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
	ImGui::End();
}