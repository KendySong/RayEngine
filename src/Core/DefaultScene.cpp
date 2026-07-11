#include "DefaultScene.hpp"
#include "../Settings.hpp"

#include <iostream>

DefaultScene::DefaultScene() : m_view(ViewMode::FPS), m_assetManager(RE::AssetManager::instance())
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
	RE::Light* light = new RE::Light("../assets/shaders/light.vs", "../assets/shaders/light.fs");
	light->position = { -20, 15, 0 };

	RE::Light* lightRed = new RE::Light("../assets/shaders/light.vs", "../assets/shaders/light.fs");
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

	m_cube1.model = new Model(LoadModelFromMesh(GenMeshCube(4.0f, 4.0f, 4.0f)));
	m_cube2.model = new Model(LoadModelFromMesh(GenMeshCube(4.0f, 4.0f, 4.0f)));
	m_cube1.model->materials[0].shader = m_assetManager.shader["lightRed"]->shader;
	m_cube2.model->materials[0].shader = m_assetManager.shader["lightRed"]->shader;

	m_ground.model = new Model(LoadModelFromMesh(GenMeshPlane(100, 100, 1, 1)));
	m_ground.model->materials[0].shader = m_assetManager.shader["light"]->shader;
	m_ground.transform.position = { 0, 0, 0 };

	//Define key with actions
	RE::Input::instance().viewFPS.hold[KEY_E] = [&]() -> void {
		b3Body_ApplyLinearImpulseToCenter(m_bodyID1, { 0, 10, 0 }, true);
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
		
	m_assetManager.shader["light"]->updateUniform();
	m_assetManager.shader["lightRed"]->updateUniform();
	m_assetManager.animator["robot"].update();

	//Physics
	b3World_Step(m_worldID, dt, Settings::subStepCount);
	m_cube1.transform.position = b3Body_GetPosition(m_bodyID1);
	m_cube1.transform.rotation = b3Body_GetRotation(m_bodyID1);

	m_cube2.transform.position = b3Body_GetPosition(m_bodyID2);
	m_cube2.transform.rotation = b3Body_GetRotation(m_bodyID2);


}

void DefaultScene::render()
{
	//Draw on the texture
	BeginTextureMode(m_pixelised.target);
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
	EndTextureMode();

	//Render texture
	ClearBackground({ 30, 30, 30 });
	DrawTexturePro(m_pixelised.target.texture, 
		{ 0, 0, (float)m_pixelised.width,  -(float)m_pixelised.height }, 
		{ 0, 0, (float)Settings::width, (float)Settings::height }, 
		Vector2(0, 0), 
		0, 
		WHITE
	);
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