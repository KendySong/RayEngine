#pragma once
#include <vector>
#include <string>
#include <Raylib/raylib.h>

#include <ImGui/rlImGui.h>
#include <Imgui/imgui.h>

namespace RE
{
    class Animator
    {
    public:
        Animator() = default;
        Animator(const char* path, Model* model);
        void update();
        void setCurrent(int index);
        void setCurrent(const char* name);
        void gui();

        float speed;

    private:
        int m_count;
        int m_index;
        float m_frame;
        Model* m_model;
        ModelAnimation* m_modelAnim;
        const char* m_current;

        std::vector<const char*> m_animName;
    };
}
