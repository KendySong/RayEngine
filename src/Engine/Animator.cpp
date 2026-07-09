#include "Animator.hpp"
#include "../Settings.hpp"

Animator::Animator(const char* path, Model* model) : m_index(0), m_frame(0), m_model(model)
{
    m_modelAnim = LoadModelAnimations(path, &m_count);

    m_animName.reserve(m_count);
    for (size_t i = 0; i < m_count; i++)
    {
        m_animName.emplace_back(m_modelAnim[i].name);
    }

    speed = Settings::defaultAnimSpeed;
}

void Animator::update()
{
    m_frame += GetFrameTime() * speed;
    m_frame = fmodf(m_frame, m_modelAnim[m_index].keyframeCount);

    UpdateModelAnimation(*m_model, m_modelAnim[m_index], m_frame);
}

void Animator::setCurrent(int index)
{
    m_index = index;
}

void Animator::setCurrent(const char* name)
{
    for (size_t i = 0; i < m_count; i++)
    {
        if (name == m_modelAnim[i].name)
        {
            m_index = i;
            return;
        }
    }
    m_index = 0;
}

void Animator::gui()
{ 
    static const char* current = m_animName[0];
    if (m_count <= 0)
    {
        return;
    }

    ImGui::SeparatorText("Animation");
    ImGui::DragFloat("Speed", &speed, 0.1f);
   
    if (ImGui::BeginCombo("Animations", current))
    {
        for (int i = 0; i < m_animName.size(); i++)
        {
            bool selected = (current == m_animName[i]);
            if (ImGui::Selectable(m_animName[i], selected))
            {
                current = m_animName[i];
                m_index = i;
            }

            if (selected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
}

