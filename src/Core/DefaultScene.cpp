#include "DefaultScene.hpp"
#include "../Settings.hpp"

DefaultScene::DefaultScene() : m_view(ViewMode::FPS)
{	
	AssetManager& assetManager = AssetManager::instance();
	
	//Load shader
	m_light = Light("../assets/shaders/light.vs", "../assets/shaders/light.fs");

	//Load and configure assets
	assetManager.texture["castle"] = LoadTexture("../assets/textures/castle_diffuse.png");
	assetManager.modele["castle"] = LoadModel("../assets/models/castle.obj");

	assetManager.setModeleTexture("castle", MATERIAL_MAP_DIFFUSE, assetManager.texture["castle"]);
	assetManager.setMaterialShader("castle", m_light.shader);

	//Setup game object
	m_castle.model = &assetManager.modele["castle"];
	//m_castle.transform.translation = { 90, 0, 0 };
}

void DefaultScene::update()
{
	float dt = GetFrameTime();
	if (!Settings::editMode)
	{
		m_view.update();
	}
		
	//Set shaders value
	m_light.updateUniform();
}

void DefaultScene::render()
{
	ClearBackground({ 30, 30, 30 });

	BeginMode3D(m_view.camera3D);	
		m_castle.draw();
		DrawLine3D({ 0, 0, 0 }, { 10, 0, 0 }, RED);
		DrawLine3D({ 0, 0, 0 }, { 0, 10, 0 }, GREEN);
		DrawLine3D({ 0, 0, 0 }, { 0, 0, 10 }, BLUE);
	EndMode3D();
}

void DefaultScene::gui()
{
	ImGui::Begin("Settings");
		ImGui::Text("FPS : %i", GetFPS());		
		m_light.gui();
		m_castle.gui();
		m_view.gui();
	ImGui::End();
}