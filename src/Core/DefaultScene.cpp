#include "DefaultScene.hpp"
#include "../Settings.hpp"

DefaultScene::DefaultScene() : m_view(ViewMode::FPS), m_assetManager(AssetManager::instance())
{
	//Load model, texture, shader and configure assets
	m_assetManager.texture["castle"] = LoadTexture("../assets/textures/castle_diffuse.png");
	m_assetManager.modele["castle"] = LoadModel("../assets/models/castle.obj");
	m_assetManager.shader["light"] = new Light("../assets/shaders/light.vs", "../assets/shaders/light.fs");

	m_assetManager.setModeleTexture("castle", MATERIAL_MAP_DIFFUSE, m_assetManager.texture["castle"]);
	m_assetManager.setMaterialShader("castle", m_assetManager.shader["light"]->shader);

	//Setup game object
	m_castle.model = &m_assetManager.modele["castle"];
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
	m_assetManager.shader["light"]->updateUniform();
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
		m_assetManager.shader["light"]->gui();
		m_castle.gui();
		m_view.gui();
	ImGui::End();
}