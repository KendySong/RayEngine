# RayEngine
Mini game engine for 3D and 2D games with RayLib and ImGui</br>

## Description
- Input
- Scene
- Assets
- Animation are supported for .iqm et .glb files

## How to take the project
```git
git clone https://github.com/KendySong/RayEngine.git
cd RayEngine
premake5 vs2026
```

## Used libraries
- Raylib
- RayGui
- Box3D
- ImGui

## Scene management
Scene management inside Window.cpp

```C++
//Load scenes
MenuScene  menu;
LevelScene level;

SceneManager::instance().scenes["menu"] = &menu;
SceneManager::instance().scenes["level"] = &level;
SceneManager::instance().setCurrent("menu");
```

All scenes have to derive from SceneSkeleton abstract class
```C++
class SceneSkeleton
{
public :
    SceneSkeleton() = default;
    virtual ~SceneSkeleton();

	virtual void update() = 0;
	virtual void gui() = 0;
	virtual void render() = 0;

private :
};
```

## Shader model

All custom shaders have to derive from ShaderSkeleton abstract class
```C++
#include <raylib/raylib.h>

class ShaderSkeleton
{
public :
	ShaderSkeleton() = default;
	virtual ~ShaderSkeleton();

	virtual void updateUniform();
	virtual void gui();

	Shader shader;

private :
};
```

Exemple
```C++
#include <Raylib/raylib.h>
#include <Raylib/rlgl.h>

#include "Model/ShaderSkeleton.hpp"

class Light : public ShaderSkeleton
{
public :
	Light() = default;
	Light(const char* vsPath, const char* fsPath);

	void updateUniform() override;
	void gui() override;
	
	Vector3 color;
	Vector3 position;

private : 
	int u_color;
	int u_position;
};
```

## Assets management
Every GameObject from GameObject class will point to a model from the asset manager singleton.
Each asset has to be stored directly in the asset manager for avoiding memory bug
```C++
//Load shader
light = Light("../assets/shaders/light.vs", "../assets/shaders/light.fs");

//Load and configure assets
AssetsManager& manager = AssetManager::instance();
manager.texture["name1"] = LoadTexture("castle_diffuse.png");
manager.modele["name2"] = LoadModel("castle.obj");

manager.setModeleTexture("name1", MATERIAL_MAP_DIFFUSE, manager.texture["name1"]);
manager.setMaterialShader("name2", m_light.shader);
```

## Input management
Bind a function with a key
```C++
Input::instance().viewFPS.hold[KEY_W] = [&]() -> void {
	this->camera3D.position += direction * speed * dt;
};
```

Possible to add KeyEvent for others situation and choice when to execute it
```C++
class Input
{
public :
	void executeNavigation();
	void executeViewDrag2D();
	void executeViewFPS();

	//input-function binding foreach situation
	KeyEvent navigation;
	KeyEvent viewDrag2D;
	KeyEvent viewFPS;
};
```