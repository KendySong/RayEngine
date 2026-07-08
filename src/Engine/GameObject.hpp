#pragma once

#include <raylib/raylib.h>
#include <raylib/raymath.h>


class GameObject
{
public :
    GameObject();
    void draw();
    void gui();

    Model* model;
    Transform transform;

private :

};