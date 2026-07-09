#include "DefaultScene.hpp"
#include "../Settings.hpp"

DefaultScene::DefaultScene() : m_view(ViewMode::FPS), m_assetManager(AssetManager::instance())
{
	//Configure the shaders
	Light* light = new Light("../assets/shaders/light.vs", "../assets/shaders/light.fs");
	light->position = { -20, 0, 0 };

	Light* lightRed = new Light("../assets/shaders/light.vs", "../assets/shaders/light.fs");
	lightRed->position = { -20, 0, -40 };
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
}

void DefaultScene::render()
{
	ClearBackground({ 30, 30, 30 });

	static  bool showMessageBox = false;
	if (GuiButton({ 24, 24, 120, 30 }, "#191#Show Message")) showMessageBox = true;

	if (showMessageBox)
	{
		int result = GuiMessageBox({ 85, 70, 250, 100 },
			"#191#Message Box", "Hi! This is a message!", "Nice;Cool");

		if (result >= 0) showMessageBox = false;
	}


	BeginMode3D(m_view.camera3D);	
		m_castle.draw();
		m_robot.draw();
		m_turret.draw();
		DrawLine3D({ 0, 0, 0 }, { 10, 0, 0 }, RED);
		DrawLine3D({ 0, 0, 0 }, { 0, 10, 0 }, GREEN);
		DrawLine3D({ 0, 0, 0 }, { 0, 0, 10 }, BLUE);
	EndMode3D();
}

void DefaultScene::gui()
{
	ImGui::Begin("Settings");
		ImGui::Text("FPS : %i", GetFPS());		
		m_assetManager.shader["light"]->gui();
		m_assetManager.animator["robot"].gui();
		m_castle.gui();
		m_view.gui();
	ImGui::End();
}